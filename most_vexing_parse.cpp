/**
 * @file most_vexing_parse.cpp
 * @brief
 * @version 1.0
 * @date 03/29/2016 05:08:17 PM
 * @author sammieliu,sammieliu@tencent.com 
 * @copyright Copyright 1998 - 2016 Tencent. All Rights Reserved.
 */
class Timer {
 public:
  Timer() {}
};

class TimeKeeper {
 public:
  TimeKeeper(const Timer& t) {}

  int get_time() { return 0; }
};

typedef Timer Goo();
typedef TimeKeeper Foo(Goo);

TimeKeeper foo(Goo g) {
    return TimeKeeper(g());
} 

int main() {
//  TimeKeeper time_keeper(Timer());
  TimeKeeper time_keeper((Timer()));

  Foo *pf = &foo;

  return time_keeper.get_time();
}

