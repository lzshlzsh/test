/**
 * @file sizeofXYZA.cpp
 * @brief
 * @version 1.0
 * @date 11/17/2015 10:36:33 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <iostream>

using namespace std;

class X {};
class Y: virtual public X {};
class Z: virtual public X {};
class A: public Y, public Z {};

int main()
{
    Y y;
    A a;
    X &x1 = y;;
    X &x2 = a;
    
    cout << "sizeof(X) = " << sizeof(X) << endl;
    cout << "sizeof(Y) = " << sizeof(Y) << endl;
    cout << "sizeof(Z) = " << sizeof(Z) << endl;
    cout << "sizeof(A) = " << sizeof(A) << endl;

    cout << &y << "," << &x1 << endl;
    cout << &a << "," << &x2 << endl;
    return 0;
}

