/**
 * @file point_to_class_member.cpp
 * @brief
 * @version 1.0
 * @date 01/18/2016 11:57:04 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdio.h>

#include <iostream>

using namespace std;

/**
 * @brief 
 * @class A
 */
class A
{
public:
    /**
     * @brief
     */
    A (): x_(1), y_(2) {}
    int x_;
    int y_;
protected:
private:
};
/**
 * @brief 
 * @class B
 */
class B
{
public:
    /**
     * @brief
     */
    B (): z_(3) {}
    int z_;
protected:
private:
};

/**
 * @brief 
 * @class D
 */
class D: public A, public B
{
public:
    /**
     * @brief
     */
    D () {}
protected:
private:
};



/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
static void foo(int D::* filed, D *p) {
    cout << p->*filed << endl;
}

int main() {
    int A::* p1 = NULL;
    int A::* p2 = &A::x_;
    int A::* p3 = &A::y_;

    printf("%d,%d,%d\n", p1, p2, p3);
    if (p1 == NULL) {
        printf("p1 is NULL\n");
    } else {
        printf("p1 is non-NULL\n");
    }

    D d;

    printf("%d\n", &B::z_);
    foo(&B::z_, &d);

    return 0;
}

