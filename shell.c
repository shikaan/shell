#include "sds/sds.h"
#include <stdio.h>

int main() {
  sds s = sdsnew("Hello!");
  printf("%s\n", s);
  sdsfree(s);
  return 0;
}
