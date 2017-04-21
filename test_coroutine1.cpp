/**
 * @file test_coroutine1.cpp
 * @brief
 * @version 1.0
 * @date 11/10/2015 11:47:47 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <unistd.h>

#include <iostream>

#include "co_routine.h"

using namespace std;

void *co_routine_foo(void *arg) {
    for (; ;) {
        cout << '[' << reinterpret_cast<uint64_t>(arg) << ']'
            << __FUNCTION__ << endl;
        co_yield_ct();
        sleep(1);
    }
    return NULL;
}

int main() {
    stCoRoutine_t *co;

    for (int i = 0; i < 130000; ++i) {
        co_create(&co, NULL, co_routine_foo, reinterpret_cast<void *>(i));
        co_resume(co);
    }

    cout << __FUNCTION__ << endl;
    co_eventloop( co_get_epoll_ct(),0,0 );
    return 0;
}
