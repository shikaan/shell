#include "./test.h"
#include "../builtin.h"

int main() {
  sds raw = sdsempty();

  raw = sdscpy(raw, "cd");
  expect_eql_int(builtin_from(raw), BUILTIN_CD, "parses cd");

  raw = sdscpy(raw, "exit");
  expect_eql_int(builtin_from(raw), BUILTIN_EXIT, "parses exit");

  raw = sdscpy(raw, "another");
  expect_eql_int(builtin_from(raw), BUILTIN_UNDEFINED, "undefined in other cases");

  raw = sdscpy(raw, "an");
  expect_eql_int(builtin_from(raw), BUILTIN_UNDEFINED, "undefined in other cases (len 2)");

  raw = sdscpy(raw, "anot");
  expect_eql_int(builtin_from(raw), BUILTIN_UNDEFINED, "undefined in other cases (len 4)");

  sdsfree(raw);
  return report();
}