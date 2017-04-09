/**
 * @file nullptr.cpp
 * @brief
 * @version 1.0
 * @date 09/23/2016 11:02:13 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>


/**
 * @brief 
 * @class A
 */
class A
{
public:
    /**
     * @brief
     */
    A () {}
    int *p_;
protected:
private:
};

A a;

int main() {

    if (NULL == a.p_) {
        std::cout << "NULL" << std::endl;
    } 
    if (nullptr == a.p_) {
        std::cout << "nullptr" << std::endl;
    }

    return 0;
}

