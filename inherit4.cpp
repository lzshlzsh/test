/**
 * @file inherit4.cpp
 * @brief
 * @version 1.0
 * @date 01/18/2016 09:33:44 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>

using namespace std;


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
protected:
private:
    int i_;
};

/**
 * @brief 
 * @class B
 */
class B: public A
{
public:
    /**
     * @brief
     */
    B () {}
    virtual ~B() {}
protected:
private:
    int j;
};


int main() {
    B b;
    A *pa = &b;
    cout << sizeof(A) << ',' << sizeof(B) << endl;
    cout << &b << ',' << pa << endl;
    return 0;
}

