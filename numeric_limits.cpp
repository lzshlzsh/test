/**
* @file numeric_limits.cpp
* @brief
* @version 1.0
* @date 04/20/2017 08:33:42 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/
#include <stdio.h>
#include <stdint.h>

#include <limits>

int main() {
    printf("max(uint64_t): 0x%lx\n", std::numeric_limits<uint64_t>::max()); 
    printf("max(int64_t): 0x%lx\n", std::numeric_limits<int64_t>::max()); 
    return 0;
}

