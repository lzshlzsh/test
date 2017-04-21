/**
* @file kevent.cpp
* @brief
* @version 1.0
* @date 04/12/2017 12:02:33 AM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/

#include <sys/types.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <stdint.h>

#include <iostream>

/**
* @brief 
* @param[in]
* @param[in,out]
* @param[out]
* @return 0 if success, < 0 otherwise
*/
int main() {
    struct kevent *event;
    struct AAA *aa;

    std::cout << "sizeof(event) = " << sizeof(event)
        << std::endl;
    std::cout << "sizeof(aa) = " << sizeof(aa)
        << std::endl;
    return 0;
}
