/**
 * @file point3d.cpp
 * @brief
 * @version 1.0
 * @date 01/16/2016 03:58:06 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>
#include <cstdio>

using namespace std;

/**
 * @brief 
 * @class Point3d
 */
class Point3d
{
public:
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    static void access_order() {
        printf("%p\n", &Point3d::x_);
        printf("%p\n", &Point3d::y_);
        printf("%p\n", &Point3d::z_);
        printf("%p\n", &Point3d::d_);
        printf("%p\n", &Point3d::t_);
        printf("%p\n", &Point3d::e_);
    }
    /**
     * @brief
     */
    virtual ~Point3d();
    static Point3d origin_;
    float x_, y_, z_;
protected:
    float d_;
private:
    float t_;
public:
    float e_;
};


int main() {

    Point3d::access_order();

    return 0;
}
