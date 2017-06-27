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

    virtual int foo() {
        return this->goo();
    }
protected:
    virtual int goo() {
        cout << "in A::goo()" << endl;
        return 0;
    }
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
    virtual int goo() {
        A::goo();
        cout << "in B::goo()" << endl;
        return 0;
    }
private:
    int j;
};


int main() {
    B b;
    A *pa = &b;
    cout << sizeof(A) << ',' << sizeof(B) << endl;
    cout << &b << ',' << pa << endl;
    b.foo();
    return 0;
}

