/**
 * @file print_speed.cpp
 * @brief
 * @version 1.0
 * @date 03/02/2016 05:41:09 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdio.h>
#include <sys/time.h>

//每秒钟打印日志个数, 必须 >= 1.0
#define R2_LOG_PER_SEC 1
//令牌环算法控制打印频率，正常频率和突发频率相等，每个调用点独立控制
#define R2_CAN_LOG ({ \
    static struct timeval __start; \
    static double __water; \
    struct timeval __now; \
    bool __log = false; \
    gettimeofday(&__now, NULL); \
    __water += ((__now.tv_sec - __start.tv_sec) + (__now.tv_usec - __start.tv_usec) / 1e6) * (R2_LOG_PER_SEC); \
    __start = __now; \
    if (__water > (R2_LOG_PER_SEC)) { \
        __water = (R2_LOG_PER_SEC); \
    } \
    if (__water >= 1.0) { \
        __water -= 1.0; \
        __log = true; \
    } \
    __log; \
})

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
static void goo() {
    struct timeval t;
    gettimeofday(&t, NULL);
    if (R2_CAN_LOG) {
        printf("[%f]%s\n", t.tv_sec * 1000.0 + t.tv_usec / 1000.0, __FUNCTION__);
    }
}

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
static void foo() {
    struct timeval t;
    gettimeofday(&t, NULL);
    if (R2_CAN_LOG) {
        printf("[%f]%s\n", t.tv_sec * 1000.0 + t.tv_usec / 1000.0, __FUNCTION__);
        printf("===\n");
    }
}
int main() {
    while (1) {
        goo();
        foo();
    }
    return 0;
}

