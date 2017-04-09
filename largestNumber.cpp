/**
 * @file largestNumber.cpp
 * @brief
 * @version 1.0
 * @date 02/16/2017 11:11:14 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief >
 * @param[in] a
 * @param[in] b
 * @return
 */
bool mysort(const std::string &a, const std::string &b) {
    unsigned int i;

    for (i = 0; i < a.length() && i < b.length(); ++i) {
        if (a[i] > b[i]) {
            return true;
        } else if (a[i] < b[i]) {
            return false;
        }
    }

    if (0 == i) {
        return a.length() > b.length();
    }

    unsigned int j = i - 1;
    if (i < a.length()) {
        for (; i < a.length() && a[i] == b[j]; ++i);
        if (i == a.length()) {
            return false;
        }
        return a[i] > b[j];
    } else if (i < b.length()) {
        for (; i < b.length() && b[i] == a[j]; ++i);
        if (i == b.length()) {
            return false;
        }
        return a[j] > b[i];
    }
    return false;
}

/**
 * @brief 
 * @param[in] nums
 * @return
 */
std::string largestNumber(const std::vector<int> &nums) {
    std::string reslt;
    std::vector<std::string> strnums;
    char buf[32];

    strnums.reserve(nums.size());
    for (__typeof__(nums.begin()) it = nums.begin(); it != nums.end(); ++it) {
        snprintf(buf, sizeof(buf), "%d", *it);
        strnums.push_back(buf);
    }
    std::sort(strnums.begin(), strnums.end(), mysort);
    for (__typeof__(strnums.begin()) it = strnums.begin(); 
        it != strnums.end(); ++it) {
        reslt += *it;
    }
    
    return reslt;
}

int main(int argc, char **argv) {
    std::vector<int> nums;

    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " n1 n2 ..." << std::endl;
        return -1;
    }

    nums.reserve(argc - 1);
    for (int i = 1; i < argc; ++i) {
        nums.push_back(atoi(argv[i]));
    }

    std::cout << largestNumber(nums) << std::endl;
    return 0;
}

