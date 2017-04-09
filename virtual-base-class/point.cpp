/**
 * @file point.cpp
 * @brief
 * @version 1.0
 * @date 01/16/2016 10:52:42 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include "point.h"

using namespace std;


int main() {
    TimeProfile main("main");
    double a[3] = {1.725, 0.875, 0.478, };
    double b[3] = {0.315, 0.317, 0.838, };
    Point3d pa(1.725, 0.875, 0.478), pb(0.315, 0.317, 0.838);

    cout << "sizeof(Point1d) = " << sizeof(Point1d) << endl;
    cout << "sizeof(Point2d) = " << sizeof(Point2d) << endl;
    cout << "sizeof(Point3d) = " << sizeof(Point3d) << endl;

    {
        TimeProfile array("array");
        for (int i = 0; i < ITERATIONS; ++i) {
            b[X] = a[X] - b[Z];
            b[Y] = a[Y] + b[X];
            b[Z] = a[Z] + b[Y];
        }
    }
    cout << b[X] << ',' << b[Y] << ',' << b[Z] << endl;
    {
        TimeProfile cla("cla");
        for (int i = 0; i < ITERATIONS; ++i) {
            pb.x_ = pa.x_ - pb.z_;
            pb.y_ = pa.y_ + pb.x_;
            pb.z_ = pa.z_ + pb.y_;
        }
    }
    cout << pb.x_ << ',' << pb.y_ << ',' << pb.z_ << endl;
    {
        TimeProfile cla("foo");
        foo(pa, pb);
    }
    cout << pb.x_ << ',' << pb.y_ << ',' << pb.z_ << endl;
    return 0;
}
