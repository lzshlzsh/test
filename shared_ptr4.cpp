/**
* @file shared_ptr4.cpp
* @brief
* @version 1.0
* @date 04/21/2017 11:36:57 AM
* @author sammieliu,sammieliu@tencent.com 
* @copyright Copyright 1998 - 2017 Tencent. All Rights Reserved.
*/

//  Boost shared_ptr_example.cpp  --------------------------------------------//

//  Copyright Beman Dawes 2001.  Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


//  See http://www.boost.org/libs/smart_ptr for documentation.

//  Revision History
//  21 May 01  Initial complete version (Beman Dawes)

//  The original code for this example appeared in the shared_ptr documentation.
//  Ray Gallimore pointed out that foo_set was missing a Compare template
//  argument, so would not work as intended.  At that point the code was
//  turned into an actual .cpp file so it could be compiled and tested.

#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

//  The application will produce a series of
//  objects of type Foo which later must be
//  accessed both by occurrence (std::vector)
//  and by ordering relationship (std::set).

struct Foo
{ 
    Foo( int _x ) : x(_x) {}
    ~Foo() { std::cout << "Destructing a Foo with x=" << x << "\n"; }
    int x;
    /* ... */
};

int get_func(boost::shared_ptr<void> &info) {
    info = boost::make_shared<Foo>(3);
    return 0;
}

int update_func(boost::shared_ptr<void> info) {
    Foo *c = reinterpret_cast<Foo *>(info.get());
    std::cout << __FUNCTION__ << ":c->x = " << c->x << std::endl;
    return 0;
}

int main()
{
    boost::shared_ptr<void> a(new Foo(1));
    boost::shared_ptr<void> b = boost::make_shared<Foo>(2);

    Foo *c = reinterpret_cast<Foo *>(b.get());
    std::cout << "c->x = " << c->x << std::endl;

    boost::shared_ptr<void> d;
    get_func(d);
    update_func(d);
    return 0;
}


