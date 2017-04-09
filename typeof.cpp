/**
 * @file typeof.cpp
 * @brief
 * @version 1.0
 * @date 01/09/2016 09:06:41 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>

using namespace std;

struct A {
    A(int &i): i_(i) {}
    int &i_;
};

int main() {
    int i = 1;
    A a(i);
    __typeof__(A.i_) &ii = a.i_;

    cout << a.i_ << endl;
    ii = 2;
    cout << a.i_ << endl;

    return 0;
}
