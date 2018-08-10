/**
* @file unordered_map_mem.cpp
* @brief
* @version 1.0
* @date 08/10/2018 09:51:30 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/
#include <unistd.h>
#include <stdlib.h>

#include <unordered_map>
#include <boost/functional/hash.hpp>
#include <iostream>

using Key = std::pair<uint64_t, uint64_t>;

struct Val {
  double d1,d2,d3,d4,d5,d6;
};

int main(int argc, char **argv) {
  auto feature_num = 10000000;
  std::cout << "usage: " << argv[0] << " [feature_num]" << std::endl;
  if (argc >= 2) {
    feature_num = atoll(argv[1]);
  }
  std::cout << "feature_num:" << feature_num << std::endl;

  std::unordered_map<Key, Val, boost::hash<Key>> algo_ft_params;

  std::cout << "press any key to fill feature parameters" << std::endl;
  getchar();

  for (auto i = 0; i < feature_num; ++i) {
    algo_ft_params.emplace(std::make_pair(i, i+1), Val());
  }

  std::cout << "press any key to exit..." << std::endl;
  getchar();
  return 0;
}

