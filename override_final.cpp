/**
 * @file override_final.cpp
 * @brief
 * @version 1.0
 * @date 11/24/2016 11:38:46 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <iostream>

class B 
{
public:
	virtual void f(int) {std::cout << "B::f" << std::endl;}
};

class D : public B
{
public:
	virtual void f(int) override final {std::cout << "D::f" << std::endl;}
//	virtual void f(short) override final {std::cout << "D::f" << std::endl;}
};

class F : public D
{
public:
//	virtual void f(int) override {std::cout << "F::f" << std::endl;}
};

int main() {
    return 0;
}

