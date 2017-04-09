/**
 * @file copy_construct.cpp
 * @brief
 * @version 1.0
 * @date 07/01/2016 01:45:01 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <iostream>

/**
 * @brief 
 * @class Test
 */
class Test
{
public:
    /**
     * @brief
     */
    Test (int &i): i_(i) {}
    int get() { return i_;}
    void set(int i) { i_ = i;}
protected:
private:
    int &i_;
};

int main() {
    int i = 0;
    Test a(i);
    Test b = a;

    std::cout << b.get() << std::endl;
    a.set(1);
    std::cout << b.get() << std::endl;
    return 0;
}
