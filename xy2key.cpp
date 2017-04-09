/*
 * =====================================================================================
 *
 *       Filename:  xy2key.cpp
 *
 *    Description:  G
 *
 *        Version:  1.0
 *        Created:  04/26/2015 11:29:08 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdint.h>

#include <iostream>

using namespace std;

static inline int64_t xy2key(const int x, const int y)
{
    return (static_cast<int64_t>(x) << 32) + y;
}

static inline void key2xy(const int64_t key, int &x, int &y)
{
    y = static_cast<int>(key & 0xffffffff);
    x = static_cast<int>(key >> 32);
}

int main()
{
    int x = -2;
    int y = -3;
    int64_t key;

    key = xy2key(x, y);

    cout << key << endl;
    
    key2xy(key, x, y);

    cout << x << ", " << y << endl;

    return 0;
}
