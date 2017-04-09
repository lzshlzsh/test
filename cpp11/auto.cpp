/*
 * =====================================================================================
 *
 *       Filename:  auto.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  06/05/2015 10:40:19 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template< typename LHS, typename RHS>
  auto AddingFunc(const LHS &lhs, const RHS &rhs) -> decltype(lhs+rhs)
{return lhs + rhs;}

auto foo()->int {
    return 0;
}

int main()
{
    vector<int> a;

    a.resize(10);

    iota(a.begin(), a.end(), 1);

    for (auto it = a.begin(); it != a.end(); it++) {
        cout << *it << endl;
    }

    return 0;
}
