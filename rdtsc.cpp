/*
 * =====================================================================================
 *
 *       Filename:  rdtsc.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/22/2015 11:21:45 AM
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

#ifdef __x86_64__
static inline uint64_t rdtsc()
{
    uint32_t edx, eax;
    __asm__ __volatile__(
    "rdtsc": "=d"(edx), "=a"(eax)
    );
    return (static_cast<uint64_t>(edx) << 32) | eax;
}
#else
static inline uint64_t rdtsc()
{
    uint64_t tm;
    __asm__ __volatile__(
    "rdtsc": "=A"(tm)
    );
    return tm;
}
#endif

int main(int argc, char **argv)
{
    cout << rdtsc() << endl;
    return 0;
}
