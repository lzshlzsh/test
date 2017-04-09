/*
 * =====================================================================================
 *
 *       Filename:  auto_ptr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  12/31/2013 06:54:48 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <memory>

using namespace std;

class Test
{
public:
    Test() {std::cout << "Test()" << std::endl;}
    virtual ~Test() {std::cout << "~Test()" << std::endl;}
};

class Test1: public Test {
public:
    Test1() {
        cout << "Test1()" << endl;
    }
    virtual ~Test1() {
        cout << "~Test1()" << endl;
    }
};

int test001()
{
    std::auto_ptr<Test> ptr;
    Test *p = new Test;

    ptr = std::auto_ptr<Test>(p);

    return 0;
}

int test002()
{
    char *p;
    p = new char[1 << 20];
    delete p;
    return 0;
}

int test003()
{
    Test *p;

    p = new Test[3];
    delete []p;
    return 0;
}

int test004()
{
    std::auto_ptr<Test1> p(new Test1());

    std::auto_ptr<Test> p1;
   
    p1 = p;
    
    return 0;
}

int main()
{
/*     test001();
 *     test002();
 *     test003();
 */
    test004();
    return 0;
}
