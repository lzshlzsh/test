/**
 * @file shared_ptr.cpp
 * @brief
 * @version 1.0
 * @date 01/19/2016 04:37:49 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <stdint.h>

#include <iostream>
#include <unordered_map>
#include <boost/shared_ptr.hpp>

using namespace std;

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
protected:
private:
    int i_;
};

static boost::shared_ptr<A> s_shared_a;
static boost::shared_ptr<A> s_shared_a2;

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
static void foo(boost::shared_ptr<A> xx) {
    cout << __LINE__ << ':' << xx.use_count() << endl;
}

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
static void goo(boost::shared_ptr<A> &xx) {
    cout << __LINE__ << ':' << xx.use_count() << endl;
}

static boost::shared_ptr<A> &hoo() {
    cout << __LINE__ << ':' << s_shared_a.use_count() << endl;
    s_shared_a = boost::shared_ptr<A>(new A);
    s_shared_a2 = s_shared_a;
    cout << __LINE__ << ':' << s_shared_a.use_count() << endl;
    cout << __LINE__ << ':' << s_shared_a2.use_count() << endl;
    s_shared_a2.reset();
    cout << __LINE__ << ':' << s_shared_a.use_count() << endl;
    cout << __LINE__ << ':' << s_shared_a2.use_count() << endl;
    return s_shared_a;
}

static boost::shared_ptr<A> ioo() {
    return s_shared_a;
}

static boost::shared_ptr<A> joo() {
    return boost::shared_ptr<A>();
}

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
static void test() {
    std::unordered_map<uint64_t, boost::shared_ptr<A> > taskid2_a;

    {
        boost::shared_ptr<A> p = ioo();
        cout << __LINE__ << ':' << p.use_count() << endl;
        cout << __LINE__ << ':' << s_shared_a.use_count() << endl;

        p = boost::shared_ptr<A>(new A());
        if (p.get() == nullptr) {
            cout << __LINE__ << ':' << p.get() << endl;
        }
        p.reset();
        if (p.get() == nullptr) {
            cout << __LINE__ << ':' << p.get() << endl;
        }
    }

    taskid2_a.insert(std::make_pair(1, boost::shared_ptr<A>(new A)));

    foo(taskid2_a[1]);
    goo(taskid2_a[1]);

    cout << __LINE__ << ':' << taskid2_a[1].use_count() << endl;
    cout << __LINE__ << ':' << hoo().use_count() << endl;
    {
        boost::shared_ptr<A> p = ioo();
        cout << __LINE__ << ':' << p.use_count() << endl;
        cout << __LINE__ << ':' << s_shared_a.use_count() << endl;
        p.reset();
        cout << __LINE__ << ':' << s_shared_a.use_count() << endl;
    }
    cout << __LINE__ << ':' << s_shared_a.use_count() << endl;

    boost::shared_ptr<A> jo = joo();

    cout << __LINE__ << ':' << jo.use_count() << ':' << jo.get() << endl;
}

/**
 * @brief 
 * @param[in]
 * @param[in,out]
 * @param[out]
 * @return 0 if success, < 0 otherwise
 */
int main() {

    test();

    return 0;
}
