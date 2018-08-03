/**
 * @file std_async.cpp
 * @brief
 * @version 1.0
 * @date 08/03/2018 10:29:05 AM
 * @author sammieliu,sammieliu@tencent.com
 * @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <future>

template <typename RandomIt>
int parallel_sum(RandomIt beg, RandomIt end)
{
  auto len = end - beg;
  if (len < 1000)
    return std::accumulate(beg, end, 0);

  RandomIt mid = beg + len/2;
  auto policy = std::launch::async;
//  auto policy = std::launch::deferred;
  auto handle = std::async(policy, parallel_sum<RandomIt>, mid, end);
  int sum = parallel_sum(beg, mid);

  std::future_status status;
  do {
    status = handle.wait_for(std::chrono::seconds(1));
    if (status == std::future_status::deferred) {
      std::cout << "deferred\n";
    } else if (status == std::future_status::timeout) {
      std::cout << "timeout\n";
    } else if (status == std::future_status::ready) {
      std::cout << "ready!\n";
    }
  } while (status != std::future_status::ready);

  std::cout << "=======\n";

  status = handle.wait_for(std::chrono::seconds(1));
  if (status == std::future_status::deferred) {
    std::cout << "deferred\n";
  } else if (status == std::future_status::timeout) {
    std::cout << "timeout\n";
  } else if (status == std::future_status::ready) {
    std::cout << "ready!\n";
  }

//  handle.get();
  return sum + handle.get();
}

int main()
{
  std::vector<int> v(10000, 1);
  std::cout << "The sum is " << parallel_sum(v.begin(), v.end()) << '\n';
}

