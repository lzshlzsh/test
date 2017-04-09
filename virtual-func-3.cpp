/**
 * @file virtual-func-3.cpp
 * @brief
 * @version 1.0
 * @date 01/31/2016 09:02:37 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

/**
 * @brief 
 * @class A
 */
class A
{
public:
    /**
     * @brief
     */
    A () {}
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    virtual void goo() {
    }
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    virtual void foo() {
        A::goo();
    }
    /**
     * @brief 
     * @param[in]
     * @param[in,out]
     * @param[out]
     * @return 0 if success, < 0 otherwise
     */
    virtual void koo() {
        goo();
    }
protected:
private:
};

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
int main(int argc, char **argv) {
    A a;
    a.foo();
    a.koo();
    return 0;
}
