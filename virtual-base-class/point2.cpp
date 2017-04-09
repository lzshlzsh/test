/**
 * @file point2.cpp
 * @brief
 * @version 1.0
 * @date 01/16/2016 12:14:28 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include "point.h"

using namespace std;

void foo(Point3d &pa, Point3d &pb) {
    for (int i = 0; i < ITERATIONS; ++i) {
        pb.x_ = pa.x_ - pb.z_;
        pb.y_ = pa.y_ + pb.x_;
        pb.z_ = pa.z_ + pb.y_;
    }
}

