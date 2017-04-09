/**
 * @file test_utimes.cpp
 * @brief
 * @version 1.0
 * @date 12/16/2016 10:32:09 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <sys/types.h>
#include <utime.h>

#include <iostream>


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " file" << std::endl;
        return -1;
    }

    const char *file = argv[1];

    if (0 == utime(file, NULL)) {
        std::cout << "change timestamps of " << file << " to the current time successfully" << std::endl; 
    } else {
        std::cout << "change timestamps of " << file << " failed" << std::endl; 
    }

    return 0;
}
