/**
 * @file shared_ptr3.cpp
 * @brief
 * @version 1.0
 * @date 11/10/2016 07:17:56 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
#include <iostream>
#include <set>
#include <unordered_map>

#include <boost/shared_ptr.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>

#define COUT std::cout << '[' << __FUNCTION__ << ':' << __LINE__ << ']'

class A {
    int i_;
public:
    A(const int i): i_(i) {
        COUT << "construct " << i_ << ':' << __FUNCTION__ << std::endl;
    }
    ~A() {
        COUT << "destruct " << i_ << ':' << __FUNCTION__ << std::endl;
    }
};

static std::unordered_map<int, boost::shared_ptr<A> > g_map;
static boost::shared_mutex g_mutex;

static int init() {
    for (int i = 1; i < 10; ++i) {
        g_map.insert(std::make_pair(i, boost::shared_ptr<A>(new A(i))));
    }
    return 0;
}

static void thread() {
    std::set<boost::shared_ptr<A> > set;
    for (int i = 0; i < 1000; ++i) {
        {
            boost::shared_lock<boost::shared_mutex> lock(g_mutex);
            std::unordered_map<int, boost::shared_ptr<A> >::iterator it = 
                g_map.find(i);
            if (it != g_map.end()) {
                set.insert(it->second);
            }
        }
    }
}

static void read() {
    std::set<boost::shared_ptr<A> > set;
    for (int i = 0; i < 1000; ++i) {
        std::unordered_map<int, boost::shared_ptr<A> >::iterator it = 
            g_map.find(i);
        if (it != g_map.end()) {
            set.insert(it->second);
        }
    }
}

static int test() {
    boost::thread t(thread);
    boost::thread t1(thread);
    boost::thread t2(thread);

    for (int i = 0; i < 1000; ++i) {
        {
            boost::unique_lock<boost::shared_mutex> lock(g_mutex);
            std::unordered_map<int, boost::shared_ptr<A> >::iterator it = 
                g_map.find(i);
            if (it != g_map.end()) {
                g_map.erase(it);
            }
            read();
            read();
            read();
        }
//        usleep(1500);
    }
    t.join();
    t1.join();
    t2.join();
    return 0;
}

int main() {
    init();
    test();
    return 0;
}

