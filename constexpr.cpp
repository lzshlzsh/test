/**
 * @file constexpr.cpp
 * @brief
 * @version 1.0
 * @date 11/24/2016 11:05:02 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <vector>
#include <iostream>

constexpr int foo(const int i) {
    return 1 == i ? 1 : i * foo(i - 1);
}

int main() {
    const int i = 9;
    const int j = 19;
    constexpr int k = i + j;

    std::vector<int> a(k, k);
    std::vector<int> b(foo(i), k);
    
//    k = 10;

    std::cout << a.size() << std::endl;
    std::cout << b.size() << std::endl;

    return 0;
}

