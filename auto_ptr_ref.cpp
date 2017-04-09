/**
 * @file auto_ptr_ref.cpp
 * @brief
 * @version 1.0
 * @date 11/10/2015 09:49:18 AM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2015 Tencent. All Rights Reserved.
 */

/**
 * @brief 
 * @class TestRef
 */
class TestRef
{
public:
    explicit TestRef(char *str): str_(str) {}
    char *str_;
protected:
private:
    /* ====================  DATA MEMBERS  ======================================= */
};

/**
 * @brief 
 * @class Test
 */
class Test
{
public:
    explicit Test(char *str = 0): str_(str) {}
    Test(Test &t): str_(t.str_) {}

    Test(TestRef t): str_(t.str_) {}
    operator TestRef() { return TestRef(str_); }

    char *str_;
protected:
private:
    /* ====================  DATA MEMBERS  ======================================= */
};

Test foo() {
    Test t;
    return t;
}

int main() {
    Test t = foo();
    (void)t;
    return 0;
}
