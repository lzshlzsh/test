/**
 * @file const_hash.cpp
 * @brief
 * @version 1.0
 * @date 08/24/2016 10:20:15 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <map>
#include <vector>
#include <set>
#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif
#include <time.h>
#include <math.h>

//一致性hash环中总配额
static const unsigned long long TOTAL = 1ULL << 32;
static const double FTOTAL = (double)TOTAL;

//标准库的随机算法有局限，这里用Wichman-Hill的算法

static unsigned long long x, y, z; //随机种子

//初始化随机种子
static void my_srand(unsigned long long a)
{
    x = a % 30268;
    a /= 30268;
    y = a % 30306;
    a /= 30306;
    z = a % 30322;
    a /= 30322;
    ++x;
    ++y;
    ++z;
}

//得到一个0和1之间的浮点随机数
static double my_random()
{
    x = x * 171 % 30269;
    y = y * 172 % 30307;
    z = z * 170 % 30323;
    return fmod(x / 30269.0 + y / 30307.0 + z / 30323.0, 1.0);
}

//得到一个随机的unsigned int
static unsigned int my_rand()
{
    return (unsigned int)(my_random() * TOTAL);
}

using namespace std;

#define M_NUM 2000 //机器数
#define VNODE_NUM 100 //每台机器虚节点数

//各机器配额相对配额均值的最大浮动比率
#define RATE 0.05
#define RATE_MIN (1 - RATE)
#define RATE_MAX (1 + RATE)

typedef set<unsigned int> HL; //单机虚节点的hash值列表，包含VNODE_NUM个hash值
typedef vector<HL> HLL; //机器列表
typedef map<unsigned int, size_t> H2M; //存储环中已存在的节点，hash值映射机器号（HLL中的索引）
typedef map<size_t, unsigned long long> M2C; //机器号映射其在环中的配额

//随机构造一个hash列表，输入的hl可能已有部分值，见下面的算法
static void generate_hash(HL &hl)
{
    while (hl.size() < VNODE_NUM)
    {
        hl.insert(my_rand());
    }
}

static HLL hll(M_NUM); //存储所有机器
static H2M h2m; //环，hash:index
static M2C m2c; //环中各机器的配额

//判断是否平衡
static bool is_balance()
{
    double avg = FTOTAL / m2c.size(); //平均配额
    for (M2C::iterator iter = m2c.begin(); iter != m2c.end(); ++iter)
    {
        double rate = (*iter).second / avg;
        if (rate < RATE_MIN || rate > RATE_MAX)
        {
            //某台机器和平均配额的比率越界，不平衡
            return false;
        }
    }
    return true; //平衡
}

static FILE *result_fp;

//记录一台机器的结果到文件
static void record(HL &hl, size_t idx)
{
    fprintf(result_fp, "#%llu\n", (unsigned long long)idx);
    for (HL::iterator iter = hl.begin(); iter != hl.end(); ++iter)
    {
        fprintf(result_fp, "%u\n", *iter);
    }
    fflush(result_fp);
}

int main(int argc, char *argv[])
{
    //初始化
#ifdef WIN32
    unsigned long long start_time = GetTickCount();
    my_srand(start_time * start_time);
#else
    if (argc != 2 || strlen(argv[1]) < 10) //linux下需要给一个足够长度的argv[1]，存放实时监控
    {
        return 1;
    }

    struct timeval tm;
    gettimeofday(&tm, NULL);
    unsigned long long start_time = tm.tv_sec * 1000000ULL + tm.tv_usec;
    my_srand(start_time);
#endif
    char fn[100];
    sprintf(fn, "conhash_result_vnode_%d_ratio_%f.txt.%llu", VNODE_NUM, RATE, start_time);
    result_fp = fopen(fn, "w");
    if (result_fp == NULL)
    {
        return 1;
    }

    //第一台机器随便构造一个
    generate_hash(hll[0]);
    for (HL::iterator it = hll[0].begin(); it != hll[0].end(); ++it)
    {
        h2m[*it] = 0;
    }
    m2c[0] = TOTAL;
    record(hll[0], 0);

    for (size_t i = 1; i < M_NUM; ++i)
    {
        HL &hl = hll[i];

        //反复试验构造机器#i的hash列表
        for (;;)
        {
            HL save_hl = hl; //存一下

            generate_hash(hl);

            //检查hash值是否和之前有冲突
            bool dup_h = false;
            for (HL::iterator it = hl.begin(); it != hl.end(); ++it)
            {
                if (h2m.find(*it) != h2m.end())
                {
                    dup_h = true;
                    break;
                }
            }
            if (dup_h)
            {
                //有冲突，恢复hl重来
                hl = save_hl;
                continue;
            }

            unsigned long long &count = m2c[i]; //用于记录当前机器配额
            M2C m2c_diff; //记录分裂节点的调整量，用于回滚
            H2M h2m_split; //记录每个hash对应的分裂的节点，用于下面的启发式算法
            //向环中增加节点的同时调整配额，注意grocery系统的设计，每个节点的配额是其前面一段，即(*ins_iter).first - (*last_iter).first
            for (HL::iterator it = hl.begin(); it != hl.end(); ++it)
            {
                H2M::iterator ins_iter = h2m.insert(H2M::value_type(*it, i)).first; //插入同时获取位置
                //获取前后位置
                H2M::iterator next_iter = ins_iter;
                ++next_iter; //获取下一个位置
                if (next_iter == h2m.end())
                {
                    next_iter = h2m.begin();
                }
                H2M::iterator last_iter = ins_iter;
                if (ins_iter == h2m.begin())
                {
                    last_iter = h2m.end();
                }
                --last_iter; //获取上一个位置
                size_t split_idx = (*next_iter).second; //被分裂节点的索引
                unsigned long long new_count = (*it + TOTAL - (*last_iter).first) % TOTAL; //机器获取到的配额
                if (i == split_idx)
                {
                    //被分裂节点和当前节点同机器，顺着环向后找真正被分裂的机器
                    H2M::iterator tmp = next_iter;
                    for (;;)
                    {
                        ++tmp;
                        if (tmp == h2m.end())
                        {
                            tmp = h2m.begin();
                        }
                        if ((*tmp).second != i)
                        {
                            h2m_split[*it] = (*tmp).second;
                            break;
                        }
                    }
                    //同机器的节点相邻，无需调整配额
                }
                else
                {
                    h2m_split[*it] = split_idx;
                    count += new_count; //给新节点增加配额
                    m2c[split_idx] -= new_count; //被分裂节点减少对应配额
                    m2c_diff[split_idx] += new_count; //记录diff
                }
            }

            if (is_balance())
            {
                //成功找到一个机器的虚节点hash列表，跳出去继续找下一个
                break;
            }

            //不平衡，回滚，先从环中删除当前机器节点
            for (HL::iterator it = hl.begin(); it != hl.end(); ++it)
            {
                h2m.erase(*it);
            }
            m2c.erase(i); //再从配额表中删除当前机器
            //然后回滚受影响的机器的配额变化
            for (M2C::iterator diff_iter = m2c_diff.begin(); diff_iter != m2c_diff.end(); ++diff_iter)
            {
                m2c[(*diff_iter).first] += (*diff_iter).second;
            }

            //启发式算法，根据被split的节点所在机器的配额决定是否保留已算出的hash值
            double avg = FTOTAL / m2c.size();
            for (HL::iterator it = hl.begin(); it != hl.end();)
            {
                double diff = m2c[h2m_split[*it]] - avg;
                if (diff <= 0)
                {
                    //这个hash值分裂了低于平均配额值的机器，只会加剧不平衡，因此去掉
                    hl.erase(it++);
                }
                else
                {
                    //这个hash值分裂了高于平均配额值的机器，对整体平衡性是有利的，保留
                    ++it;
                }
            }
            if (hl.size() == VNODE_NUM)
            {
                //全部hash都分裂配额均值以上的机器，但是死局了，重头再来
                hl.clear();
            }
        }
        //找到了一个解，记录并打日志
        record(hl, i);
#ifdef WIN32
        time_t tm;
        time(&tm);
        cout << asctime(localtime(&tm)) << i + 1 << endl;
#else
        sprintf(argv[1], "%u", (unsigned int)i); //更新进度，这样可以在top或ps中看到
#endif
    }
    //处理完毕
    cout << "done" << endl;
    fclose(result_fp);

    return 0;
}


