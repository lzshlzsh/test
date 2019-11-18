/*
 * =====================================================================================
 *
 *       Filename:  test_set.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/04/2015 04:13:59 PM
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
#include <utility>

using namespace std;

struct Gps {
    int x_;
    int y_;
    Gps(): x_(0), y_(0) {}
    Gps(int x, int y): x_(x), y_(y) {}
};

int X = 10;
int Y = 20;

struct GpsLess {
  bool operator() (const Gps &a, const Gps &b) const {
      return (a.x_ - X) + (a.y_ - Y) < (b.x_ - X) + (b.y_ - Y);
  }  
};

int main()
{
  typedef set<std::pair<int, double>> GpsSet;
  GpsSet gps_set;

  for (int i = 50; i > 40; i--) {
    gps_set.insert(std::make_pair(i, 50-i));
  }

  for (auto const &it: gps_set) {
    cout << it.first << ' ' << it.second << '\n';
  }

  std::pair<int, double> a(1, 4), b(5, 1);
  if (!(a >= b)) {
    cout << "<\n";
  } else {
    cout << ">=\n";
  }
  
//  typedef set<Gps, GpsLess> GpsSet;
//
//  GpsSet gps_set;
//
//  for (int i = 50; i > 40; i--) {
//    gps_set.insert(Gps(i, i+1));
//  }
//
//  for (GpsSet::const_iterator it = gps_set.begin(); it != gps_set.end(); it++) {
//    cout << it->x_ << ", " << it->y_ << endl;
//  }
//
//  for (GpsSet::iterator it = gps_set.begin(); it != gps_set.end(); ++it) {
//    gps_set.erase(it);
//  }
//
//  cout << gps_set.size() << endl;
//
  return 0;
}
