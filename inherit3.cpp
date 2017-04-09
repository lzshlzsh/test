/**
 * @file inherit3.cpp
 * @brief
 * @version 1.0
 * @date 01/08/2016 10:18:02 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>

using namespace std;

class A {
public:
    static void set(const int i) {
        instance().i_ = i;
    }
    static int get() {
        return instance().i_;
    }
private: 
    static A &instance() {
        static A inst;
        return inst;
    }
    int i_;
};

class B: public A {

};

class C: public A {

};

static void print() {
    cout << "A: " << A::get() << endl;
    cout << "B: " << B::get() << endl;
    cout << "C: " << C::get() << endl;
    cout << "*******" << endl;
}

int main() {
    print();
    A::set(1);
    print();
    B::set(2);
    print();
    C::set(3);
    print();

    return 0;
}
