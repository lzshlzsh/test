/**
 * @file macro-cpp2.cpp
 * @brief
 * @version 1.0
 * @date 06/16/2016 11:40:25 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>

using namespace std;

#define A(_a_) "ads"
#define B "cde"

#define __GET_ARG_N(...) __ARG_N(__VA_ARGS__)
#define __ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N
#define __ARG_SEQ() 8,7,6,5,4,3,2,1,0
#define __JOIN(a, b) a##b
#define JOIN(a, b) __JOIN(a, b)

#define GET_ARG_N_1(a, ...) __GET_ARG_N(__VA_ARGS__, __ARG_SEQ())
#define GET_ARG_N(...) GET_ARG_N_1(a, __VA_ARGS__)

int main() {
    cout << GET_ARG_N() << endl;
    cout << GET_ARG_N(a) << endl;
    cout << GET_ARG_N(a, b) << endl;
    cout << GET_ARG_N(a, b, c) << endl;
    cout << GET_ARG_N(a, b, c, d) << endl;
    cout << GET_ARG_N(a, b, c, d, e) << endl;
    cout << GET_ARG_N(a, b, c, d, e, f) << endl;
    cout << GET_ARG_N(a, b, c, d, e, f, g) << endl;
    cout << GET_ARG_N(a, b, c, d, e, f, g, h) << endl;

    JOIN(GET_ARG_N(a), 1);
    return 0;
}

