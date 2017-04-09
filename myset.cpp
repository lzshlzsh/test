/*
 * =====================================================================================
 *
 *       Filename:  myset.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  08/21/2015 03:24:59 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <set>
#include <iostream>

using namespace std;

struct Uin {
  int uin_;
  int time_;

  Uin(int uin, int time): uin_(uin), time_(time) {}
};

struct UinLess {
    bool operator() (const Uin &x, const Uin &y) const {
        return x.uin_ < y.uin_;
    }
};

int main()
{
    std::set<Uin, UinLess> myset;

    myset.insert(Uin(1, 2));
    myset.insert(Uin(1, 3));
    myset.insert(Uin(2, 4));
    myset.insert(Uin(2, 5));

    for (std::set<Uin, UinLess>::const_iterator it = myset.begin(); it != myset.end(); ++it) {
        cout << it->uin_ << ", " << it->time_ << endl;
    }

    return 0;
}
