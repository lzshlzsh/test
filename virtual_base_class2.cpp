/**
 * @file virtual_base_class2.cpp
 * @brief
 * @version 1.0
 * @date 01/16/2016 12:26:25 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <stdint.h>

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
    A ();
protected:
private:
    uint64_t i_;
};

/**
 * @brief 
 * @class B
 */
class B
{
public:
    /**
     * @brief
     */
    B ();
    virtual void foo() {}
protected:
private:
    int j_;
};


/**
 * @brief 
 * @class C
 */
class C
{
public:
    /**
     * @brief
     */
    C ();
    virtual void goo() {}
protected:
private:
    int k_;
};


/**
 * @brief 
 * @class D
 */
class D: public A, public B, public C
{
public:
    /**
     * @brief
     */
    D ();
protected:
private:
};


int main() {
    cout << sizeof(D) << endl;
    return 0;
}

