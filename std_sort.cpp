// sort algorithm example
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <vector>       // std::vector

bool myfunction (int i,int j) { return (i>=j); }

struct myclass {
  bool operator() (int i,int j) { return (i<=j);}
} myobject;

int main () {
  int myints[] = {3,3,3,3,3,3,3,3};
  std::vector<int> myvector (myints, myints+8);

  std::sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)
  std::sort (myvector.begin(), myvector.end(), myfunction);     //(12 26 32 33 45 53 71 80)

  // print out content:
  std::cout << "myvector contains:";
  for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
    std::cout << ' ' << *it;
  std::cout << '\n';

/*  std::vector<int>::iterator it = myvector.begin();
  std::cout << (int)it << std::endl;
  it--;
  std::cout << (int)it << std::endl; */

  return 0;
}
