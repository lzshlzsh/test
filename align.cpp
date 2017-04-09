/*
 * =====================================================================================
 *
 *       Filename:  align.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04/30/2015 09:37:21 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>

using namespace std;

template <typename T>
static inline T align_floor(const T v, const T align)
{
//    return v / align * align;
    return v - v % align;
}
template <typename T>
static inline T align_ceil(const T v, const T align)
{
    return (v + align - 1) / align * align;
}

int main(int argc, char **argv)
{

    cout << align_floor(123, 5) << endl;
    cout << align_ceil(123, 5) << endl;
    cout << align_floor(-123, 5) << endl;
    cout << align_ceil(-123, 5) << endl;


    return 0;
}
