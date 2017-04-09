/*
 * =====================================================================================
 *
 *       Filename:  test_map.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/21/2015 11:07:49 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <stdint.h>

#include <map>
#include <iostream>

using namespace std;

struct Gps {
    Gps(): x_(0), y_(0) {}
    int x_;
    int y_;
};

struct GpsLess {
    int operator() (const Gps &a, const Gps &b) const {
        return ((static_cast<uint64_t>(a.x_) << 32) | a.y_) < ((static_cast<uint64_t>(b.x_) << 32) | b.y_);
    }
};

int main()
{
    map<Gps, int, GpsLess> a;
    Gps gps;

    a[gps] = 1;

    gps.x_ = 43;
    gps.y_ = 23;
    a[gps] = 2;

    gps.x_ = 4;
    gps.y_ = 2;
    a[gps] = 3;

    for (map<Gps, int, GpsLess>::const_iterator it = a.begin(); it != a.end(); it++) {
        cout << it->first.x_ << "\t" << it->first.y_ << "\t" << it->second << endl;
    }

    return 0;
}
