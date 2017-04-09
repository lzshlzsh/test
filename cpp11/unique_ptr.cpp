/*
 * =====================================================================================
 *
 *       Filename:  unique_ptr.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/05/2015 11:05:09 PM
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

#define foo(p) foo_(p, __LINE__)

void foo_(int* p, const int lineno)
{
    std::cout << lineno << ":" << *p << std::endl;
}

class Test {
    std::unique_ptr<int> p_;
    Test(std::unique_ptr<int> p) {
        p_ = std::move(p);
    }
};

int main() 
{
    std::unique_ptr<int> p1(new int(42));
    std::unique_ptr<int> p2 = std::move(p1); 
    // transfer ownership
    std::unique_ptr<int> p3 = move(p2);

    if(p1) {
        (*p1)++;
        foo(p1.get());
    }

    if(p2) {
        (*p2)++;
        foo(p2.get());
    }

    if(p3) {
        (*p3)++;
        foo(p3.get());
    }
}
