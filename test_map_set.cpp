/*
 * =====================================================================================
 *
 *       Filename:  test_map_set.cpp
 *
 *    Description:  i
 *
 *        Version:  1.0
 *        Created:  08/05/2015 07:51:47 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  sammieliu (), sammieliu@tencent.com
 *   Organization:  
 *
 * =====================================================================================
 */
#include <stdint.h>

#include <map>
#include <set>
#include <iostream>
#include <string>

using namespace std;

struct Host {  
    std::string ip_;
    uint16_t port_;
    Host(): port_(0) {}
    Host(const std::pair<std::string, uint16_t> &host): ip_(host.first), port_(host.second) {}
    Host(const std::string &ip, uint16_t port): ip_(ip), port_(port) {}
    bool operator <(const Host &rvalue) const {
        return (ip_ < rvalue.ip_) || ((ip_ == rvalue.ip_ )&& ( port_ < rvalue.port_));
    }
};

int main(int argc, char **argv)
{
    std::map<Host, int> m;
    std::set<Host> s;

    m.insert(std::pair<Host, int>(Host("10.121.88.133", 6380), 1));
    m.insert(std::pair<Host, int>(Host("10.121.88.134", 6380), 2));
    m.insert(std::pair<Host, int>(Host("10.121.88.135", 6380), 3));

    for (std::map<Host, int>::iterator it = m.begin(); it != m.end(); ++it) {
        cout << it->first.ip_ << ":" << it->first.port_ << " -- " << it->second << endl;
    }

    s.insert(Host("10.121.88.133", 6380));
    s.insert(Host("10.121.88.134", 6380));
    s.insert(Host("10.121.88.135", 6380));

    for (std::set<Host>::iterator it = s.begin(); it != s.end(); ++it) {
        cout << it->ip_ << ":" << it->port_ << endl;
    }
    return 0;
}
