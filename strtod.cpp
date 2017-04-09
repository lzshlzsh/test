/**
 * @file strtod.cpp
 * @brief
 * @version 1.0
 * @date 05/20/2016 10:11:24 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdlib.h>

#include <string>
#include <iostream>

int main() {
    std::string str;
    double d = strtod(str.data(), NULL);

    std::cout << d << std::endl;
    str = "0.001";
    d = strtod(str.data(), NULL);
    std::cout << d << std::endl;

    return 0;
}

