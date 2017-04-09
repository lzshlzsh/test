/**
 * @file cin_test.cpp
 * @brief
 * @version 1.0
 * @date 02/19/2017 11:37:34 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */
#include <iostream>
#include <fstream>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " file" << std::endl;
        return -1;
    }

    std::ifstream in;
    int x, y, t;
    
    in.open(argv[1]);
    if (in.fail()) {
        std::cout << "fail to open " << argv[1] << std::endl;
        return -1;
    }

    while (!in.eof()) {
        in >> x >> y >> t;
        if (in.eof()) {
            break;
        }
        std::cout << x << '\t' << y << '\t' << t << std::endl;
    }

    return 0;
}

