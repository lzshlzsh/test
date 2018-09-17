/**
* @file test_lower_bound.cpp
* @brief
* @version 1.0
* @date 09/17/2018 04:12:02 PM
* @author sammieliu,sammieliu@tencent.com
* @copyright Copyright 1998 - 2018 Tencent. All Rights Reserved.
*/

#include <iostream>
#include <algorithm>
#include <vector>

namespace {

template<typename _Key, typename _Tp>
struct __KeyValue
{
  _Key key_;
  _Tp data_;
  inline bool operator< (const __KeyValue &o) const
  {
    return key_ < o.key_;
  }
};

template<typename _Key>
struct __KeyRangeInfo
{
    _Key key_;
    size_t begin_;
    size_t end_;
    inline bool operator<(const __KeyRangeInfo &o) const
    {
        return key_ < o.key_;
    }
};

template<typename _Key, typename _TP, typename _ValueCompare>
inline bool __key_value_type_sort(const __KeyValue<_Key, _TP> &a, const __KeyValue<_Key, _TP> &b)
{
  _ValueCompare __compare;
  return a.key_ < b.key_ || (!(b.key_ < a.key_) && __compare(a.data_, b.data_));
}

template<typename _Key, typename _Tp, typename _ValueCompare>
inline void sort_mem_map_key_value(std::vector<__KeyValue<_Key, _Tp> > &a)
{
  std::sort(a.begin(), a.end(), __key_value_type_sort<_Key, _Tp, _ValueCompare>);
}

using KeyValue = __KeyValue<int, uint64_t>;
using KeyRangeInfo = __KeyRangeInfo<int>;

} // namespace

int main() {
  uint64_t item_id = 1;
  int pool_id1 = 779279690;
  int pool_id2 = 4293489423;

  std::vector<KeyValue> data;

  for (auto i = 0; i < 10; ++i) {
    KeyValue kv;

    kv.key_ = pool_id1 + i;
    kv.data_ = item_id++;
    data.emplace_back(kv);

    kv.key_ = pool_id2 + i;
    kv.data_ = item_id++;
    data.emplace_back(kv);
  }

  sort_mem_map_key_value<int, uint64_t, std::less<uint64_t> >(data); 
 
  for (auto const &it: data) {
    std::cout << it.key_ << " " << it.data_ << std::endl;
  } 

  auto const key_size = data.size();
  auto mem = new KeyRangeInfo[key_size]; 

  for (auto i = 0u; i < key_size; ++i) {
    mem[i].key_ = data[i].key_;
  }

  KeyRangeInfo map_key;
  map_key.key_ = 4293489424;

  auto key_range = std::lower_bound(mem, mem + key_size, map_key);
  std::cout << key_size << " " << key_range-mem << std::endl;

  delete []mem;
  return 0;
}

