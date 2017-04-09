/**
 * @file convertion_operator2.cpp
 * @brief
 * @version 1.0
 * @date 11/07/2015 11:45:06 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <iostream>

using namespace std;

struct D;
struct B {
    virtual operator D() = 0;
};
struct D : B
{
    operator D() override { 
        cout << __LINE__ << endl;
        return D(); 
    }
};
 
int main()
{
    D obj;
    D obj2 = obj; // does not call D::operator D()
    B& br = obj;
    D obj3 = br; // calls D::operator D() through virtual dispatch
}
