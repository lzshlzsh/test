/**
 * @file unordered_map_inc.cpp
 * @brief
 * @version 1.0
 * @date 12/06/2016 05:55:25 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <unordered_map>
#include <iostream>

int main() {
    std::unordered_map<std::string, int> m;

    m["a"]++;
    ++m["a"];

    std::cout << m["a"] << std::endl;

    return 0;
}

