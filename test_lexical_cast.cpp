/**
* @file test_lexical_cast.cpp
* @brief
* @version 1.0
* @date 04/25/2017 08:23:43 PM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/

#include <stdint.h>

#include <boost/lexical_cast.hpp>
#include <iostream>
#include <string>

int main() {
    std::string str = "21342";
    uint64_t i = -1;

    std::cout << boost::lexical_cast<uint64_t>(str) << std::endl;
    std::cout << boost::lexical_cast<std::string>(-i) + "ex" << std::endl;
    std::cout << boost::lexical_cast<uint64_t>("b1") << std::endl;

    return 0;
}

