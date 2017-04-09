/*
 * =====================================================================================
 *
 *       Filename:  list_erease.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  07/01/2014 07:50:15 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

// erasing from list
#include <iostream>
#include <list>

using namespace std;

#define CHECK(__it) do { \
  if (__it == mylist.end()) { \
    std::cout << "end" << std::endl; \
  } \
} while (0)

int main ()
{
  std::list<int> mylist;
  std::list<int>::iterator it1,it2;

  // set some values:
  for (int i=1; i<10; ++i) mylist.push_back(i*10);

  cout << mylist.size() << endl;
  for (std::list<int>::iterator it = mylist.begin(); it != mylist.end(); ) {
      std::list<int>::iterator tmp = it;
      it++;
      mylist.erase(tmp);
  }

  cout << mylist.size() << endl;

  return 0;
  it1 = mylist.begin();
  std::cout << *it1 << std::endl;
  it1--;
  CHECK(it1);
  std::cout << *it1 << std::endl;
  it1++;
  std::cout << *it1 << std::endl;

  return 0;
                              // 10 20 30 40 50 60 70 80 90
  it1 = it2 = mylist.begin(); // ^^
  advance (it2,6);            // ^                 ^
  ++it1;                      //    ^              ^

  it1 = mylist.erase (it1);   // 10 30 40 50 60 70 80 90
                              //    ^           ^

  it2 = mylist.erase (it2);   // 10 30 40 50 60 80 90
                              //    ^           ^

  ++it1;                      //       ^        ^
  --it2;                      //       ^     ^

  it1 = it2 = mylist.erase (it1,it2);     // 10 30 60 80 90
                              //        ^

  std::cout << "it1 " << *it1 << ", it2 " << *it2 << std::endl;
  advance(it1, 7);
  std::cout << "it1 " << *it1 << ", it2 " << *it2 << std::endl;
  std::cout << "mylist contains:";
  for (it1=mylist.begin(); it1!=mylist.end(); ++it1)
    std::cout << ' ' << *it1;
  std::cout << '\n';

  return 0;
}
