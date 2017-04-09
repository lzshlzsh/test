/**
 * @file virtual_base_class3.cpp
 * @brief
 * @version 1.0
 * @date 01/16/2016 04:11:39 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdint.h>

#include <iostream>

using namespace std;


/**
 * @brief 
 * @class X
 */
class X
{
public:
protected:
private:
};

/**
 * @brief 
 * @class Y
 */
class Y: public virtual X
{
public:
protected:
private:
};

/**
 * @brief 
 * @class Z
 */
class Z: public virtual X
{
public:
protected:
private:
};

/**
 * @brief 
 * @class A
 */
class A: public Y, public Z
{
public:
protected:
private:
};

int main() {
    cout << sizeof(X) << endl;
    cout << sizeof(Y) << endl;
    cout << sizeof(Z) << endl;
    cout << sizeof(A) << endl;

    A a;
    uint64_t *p = reinterpret_cast<uint64_t *>(&a);
    cout << *p << ',' << *(p + 1) << endl;
    cout << p << endl;
    cout << *reinterpret_cast<uint64_t *>(*p - 16) << endl;
    cout << *reinterpret_cast<uint64_t *>(*(p + 1) - 16) << endl;

    return 0;
}
