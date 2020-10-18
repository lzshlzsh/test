/**
* @file test_regex_search.cpp
* @brief
* @version 1.0
* @date 04/06/2020 08:41:43 PM
* @author lzshlzsh,lzshlzsh@163.com
* @copyright Copyright 1998 - 2020 Tencent. All Rights Reserved.
*/
#include <string>
#include <iostream>

#include <boost/regex.hpp> 

namespace {

boost::regex g_expression(
  "\\[.*\\s+(\\w{8}(?:-\\w{4}){3}-\\w{12}).*\\s+(\\S+)\\s+(\\d+)\\s+(\\d{17})]"
);

} // namespace

int main() {
  std::string str = "2020-03-30 19:00:12.048 [queuedThreadPool-57106 dfd73175-f8d4-4981-8cd3-8072e0a52fbd cql-ebgioapf 7 20200406220920864] INFO  com.tencent.cloud.tstream.flink.sql.RunnerUtils  - Statements size: 4";

  boost::cmatch what;
  std::cout << "what size: " << what.size() << std::endl;
  if (boost::regex_search(str.c_str(), what, g_expression)) {
    for (auto const &it: what) {
      if (it.matched) {
        std::cout << std::string(it.first, it.second) << std::endl;
      } else {
        std::cout << "no" << std::endl;
      }
    }

    std::string str2;
    str2.reserve(str.length());
    const char *base = str.data();
    str2.append(base, what[1].first-base-1);
    str2.append(what[4].second);
    std::cout << str << std::endl;
    std::cout << str2 << std::endl;
  } else {
    std::cout << "Not match!!!" << std::endl;
  }
} 

