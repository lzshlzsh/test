/*
 * =====================================================================================
 *
 *       Filename:  lower_bound.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  09/30/2014 04:45:34 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

// map::lower_bound/upper_bound
#include <iostream>
#include <map>

int main ()
{
  std::map<char,int> mymap;
  std::map<char,int>::iterator itlow,itup;

  mymap['a']=20;
  mymap['b']=40;
  mymap['c']=60;
  mymap['d']=80;
  mymap['e']=100;
  mymap['h']=100;

  itlow=mymap.lower_bound ('b');  // itlow points to b
  itup=mymap.upper_bound ('d');   // itup points to e (not d!)

  itlow = mymap.lower_bound('f');
  if (mymap.end() == itlow) {
    std::cout << "itlow = map::end" << std::endl;
  } else {
    std::cout << itlow->first << std::endl;
  }

  itup = mymap.upper_bound('f');
  if (mymap.end() == itup) {
    std::cout << "itup = map::end" << std::endl;
  } else {
    std::cout << itup->first << std::endl;
  }

#if 0
  mymap.erase(itlow,itup);        // erases [itlow,itup)

  // print content:
  for (std::map<char,int>::iterator it=mymap.begin(); it!=mymap.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
#endif

  return 0;
}
