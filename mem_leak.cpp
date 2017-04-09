/**
 * @file mem_leak.cpp
 * @brief
 * @version 1.0
 * @date 12/12/2016 03:21:19 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <iostream>

#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    int sleeps = 1;
    int sizem = 1;
    size_t total = 0;

    if (argc >= 2) {
        sleeps = atoi(argv[1]);
    }
    if (argc >= 3) {
        sizem = atoi(argv[2]);
    }

    for (; ;) {
        size_t size = sizem << 20;

        char *buf = new char[size];
        total += sizem;
        memset(buf, 0, size);
        std::cout << "allocated mem " << total << "M, " 
            << reinterpret_cast<size_t>(buf) << std::endl;
        if (sleeps > 0) {
            sleep(sleeps);
        }
    }

    return 0;
}

