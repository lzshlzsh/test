/**
 * @file my_reference_wrapper.cpp
 * @brief
 * @version 1.0
 * @date 11/24/2016 07:41:37 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */

#include <string>
#include <iostream>

namespace my_ns {
/**
 * @brief 
 * @class Reference_wrapper
 */
template <typename T>
class reference_wrapper
{
public:
    /**
     * @brief 
     * @param[in] t
     */
    explicit reference_wrapper(T &t): t_(&t) {}
    /**
     * @brief 
     * @return
     */
    operator T & () const{
        return *t_;
    }
protected:
private:
    T *t_;
};

void foo(const std::string &str) {
    std::cout << str << std::endl;
}

}

/**
 * @brief 
 * @return 0 if success, < 0 otherwise
 */
int main() {
    std::string aa = "ads";
    std::string bb = "iop";

    my_ns::reference_wrapper<std::string> raa(aa);
    my_ns::reference_wrapper<std::string> rab(raa);
    foo(raa);

    return 0;
}
