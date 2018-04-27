/**
* @file cprime_13.46.cpp
* @brief
* @version 1.0
* @date 04/27/2018 12:52:42 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <vector>

using namespace std;

int f() {
  return 2;
}

vector<int> vi(100);

int &&r1 = f();
int &r2 = vi[0];
int &r3 = r1;
int &&r4 = vi[0] * f();

int main() {
  return 0;
}


