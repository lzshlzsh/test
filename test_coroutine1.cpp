/**
 * @file test_coroutine1.cpp
 * @brief
 * @version 1.0
 * @date 11/10/2015 11:47:47 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <iostream>

#include "co_routine.h"

using namespace std;

void *co_routine_foo(void *) {
    cout << __FUNCTION__ << endl;
    return NULL;
}

int main() {
    stCoRoutine_t *co;

    co_create(&co, NULL, co_routine_foo, NULL);
    co_resume(co);

    cout << __FUNCTION__ << endl;

    return 0;
}
