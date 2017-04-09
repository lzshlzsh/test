/**
 * @file inherit2.cpp
 * @brief
 * @version 1.0
 * @date 11/08/2015 12:04:42 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <string>
#include <iostream>

using namespace std;

class String: public string {

public:
    String(const char *str): string(str) {}
    virtual int foo() {
        return length();
    }
};

class A {
    int i;
};

class B: protected A {

};

int main(int argc, char **argv) {
//    const A &a = B();

//    A *pa = new B();

    String str = "123";
    cout << str.foo() << endl;

    return 0;
}
