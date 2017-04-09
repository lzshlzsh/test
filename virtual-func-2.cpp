/**
 * @file virtual-func-2.cpp
 * @brief
 * @version 1.0
 * @date 12/24/2015 04:48:07 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */
#include <iostream>

using namespace std;

/**
 * @brief 
 * @class Base
 */
class Base
{
public:
    Base() {}
    virtual int get() { return 0; }
protected:
private:
    /* ====================  DATA MEMBERS  ======================================= */
};


/**
 * @brief 
 * @class Derived1
 */
class Derived1: public Base
{
public:
    Derived1() {}
    virtual int get() { return 1; }
protected:
private:
    /* ====================  DATA MEMBERS  ======================================= */
};


/**
 * @brief 
 * @class Derived11
 */
class Derived11: public Derived1
{
public:
    Derived11() {}
protected:
private:
    /* ====================  DATA MEMBERS  ======================================= */
};


int main() {
    Derived11 d;
    cout << d.get() << endl;
    return 0;
}
