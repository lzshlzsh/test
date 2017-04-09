/**
 * @file sizeof2.cpp
 * @brief
 * @version 1.0
 * @date 02/20/2017 09:39:06 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
 */
#include <iostream>

struct A{
    int m;
    char c;
    long d;
};
struct B{
    int m;
    char c;
};
struct C{
    int m;
    char c;
    void* p;
};

int main() {

    std::cout << sizeof(A) << std::endl;
    std::cout << sizeof(B) << std::endl;
    std::cout << sizeof(C) << std::endl;
    return 0;
}
