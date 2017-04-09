#include <stdio.h>

#include "x.h"

int main(int argc, char **argv) {
  foo();
  int a = CONST;
  printf("[%s:%s:%d]%d\n", __FILE__, __FUNCTION__, __LINE__, a);
  return 0;
}
