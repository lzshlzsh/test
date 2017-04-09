/**
 * @file named_return_value.cpp
 * @brief
 * @version 1.0
 * @date 11/09/2015 01:25:35 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

#include <string.h>

#include <iostream>

using namespace std;

/**
 * @brief 
 * @class Test
 */
class Test
{
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    friend Test foo(double val);
public:
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    Test() {
        memset(array_, 0, sizeof(array_));
    }
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    Test(const Test &t) {
        memcpy(array_, t.array_, sizeof(array_));
    }
protected:
private:
    /* ====================  DATA MEMBERS  ======================================= */
    double array_[100];
};

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
Test foo(double val) {
    Test local;

    local.array_[0] = val;
    local.array_[99] = val;

    return local;
}

int main(int argc, char **argv) {
    for (int i = 0; i < 10000000; ++i) {
        Test t = foo(static_cast<double>(i));
        (void)t;
    }
    return 0;
}
