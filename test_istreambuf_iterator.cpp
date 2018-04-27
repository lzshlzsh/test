/**
* @file test_istreambuf_iterator.cpp
* @brief
* @version 1.0
* @date 04/03/2018 05:24:45 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <fstream>
#include <iostream>
#include <iterator>

using namespace std;

int main() {
  ifstream in("test.cpp");
  istreambuf_iterator<char> isb(in),end;
  ostreambuf_iterator<char> osb(cout);
  while(isb!=end)
    *osb++ = *isb++;
  cout<<endl;
  return 0;
}


