/**
 * @file boost_thread.cpp
 * @brief
 * @version 1.0
 * @date 11/03/2015 10:15:55 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <iostream>

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

using namespace std;

struct A {
    int i_;
    virtual ~A() {
        cout << __LINE__ << endl;
    }
};

struct B: public A {
    virtual ~B() {
        cout << __LINE__ << endl;
    }
};

struct Callable {
    Callable(A *a): a_(a) {
        cout << __LINE__ << endl;
    }
    Callable(const Callable &c) {
        cout << __LINE__ << endl;
        a_ = c.a_;
    }
    ~Callable() {
        cout << __LINE__ << endl;
    }
    void operator() () {
        cout << boost::this_thread::get_id() << endl;
        boost::this_thread::sleep_for(boost::chrono::milliseconds(100));
        cout << __LINE__ << endl;
        if (a_) {
            delete a_;
        }
    }

    A *a_;
};

static boost::mutex s_mutex;

/**
 * @brief 
 * @class DaemonThread
 */
class DaemonThread
{
public:
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    void operator() () {
        for (int i = 0; ;++i) {
//            boost::this_thread::sleep_for(boost::chrono::milliseconds(5000));
            sleep(5);
            boost::mutex::scoped_lock lock(s_mutex);
            std::cout << i << std::endl;
        }
    }
protected:
private:
};


/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
static void test() {
    boost::mutex::scoped_lock lock(s_mutex);
    boost::thread t((DaemonThread()));
    t.detach();
}

int main()
{
/*     boost::thread_group thread_group;
 * 
 *     thread_group.create_thread(Callable(new B()));
 *     thread_group.join_all();
 * 
 *     cout << "=======" << endl;
 * 
 *     thread_group.create_thread(Callable(new B()));
 *     thread_group.join_all();
 */

    test();

    while (1) {
        sleep(1);
        boost::mutex::scoped_lock lock(s_mutex);
        std::cout << "shit" << std::endl;
    }

    return 0;
}

