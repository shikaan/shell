#include "../string.h"
#include "./test.h"

void test_find() {
  sds subject = sdsnew("hello");
  char c = 'l';
  expect_eql_int(string_find(subject, c), 2, "finds first mid character");
  c = 'h';
  expect_eql_int(string_find(subject, c), 0, "finds first char");
  c = 'o';
  expect_eql_int(string_find(subject, c), 4, "finds last char");
  c = 'z';
  expect_eql_int(string_find(subject, c), -1, "does not find missing char");

  subject = sdscpylen(subject, "", 0);
  expect_eql_int(string_find(subject, c), -1, "handles empty string");

  sdsfree(subject);
}

void test_split() {
  case("happy path");
  sds subject = sdsnew("hello");
  sds* split = string_split_at(subject, 2);
  sds want_before = sdsnew("he");
  sds want_after = sdsnew("llo");
  expect_eql_int(sdscmp(split[0], want_before), 0, "first half");
  expect_eql_int(sdscmp(split[1], want_after), 0, "second half");

  want_before = sdscpy(want_before, "");
  want_after = sdscpy(want_after, "hello");

  case("at start");
  split = string_split_at(subject, 0);
  expect_eql_int(sdscmp(split[0], want_before), 0, "first half is empty");
  expect_eql_int(sdscmp(split[1], want_after), 0, "second half is full");

  case("before start");
  split = string_split_at(subject, -1);
  expect_eql_int(sdscmp(split[0], want_before), 0, "first half is empty");
  expect_eql_int(sdscmp(split[1], want_after), 0, "second half is full");

  want_before = sdscpy(want_before, "hello");
  want_after = sdscpy(want_after, "");

  case("at end");
  split = string_split_at(subject, 5);
  expect_eql_int(sdscmp(split[0], want_before), 0, "first half is full");
  expect_eql_int(sdscmp(split[1], want_after), 0, "second half is empty");

  case("after end");
  split = string_split_at(subject, 100);
  expect_eql_int(sdscmp(split[0], want_before), 0, "first half is full");
  expect_eql_int(sdscmp(split[1], want_after), 0, "second half is empty");

  case("with empty string");
  subject = sdscpy(subject, "");
  split = string_split_at(subject, 1);
  expect_eql_int(sdscmp(split[0], ""), 0, "first half is empty");
  expect_eql_int(sdscmp(split[1], ""), 0, "second half is empty");

  sdsfreesplitres(split, 2);
  sdsfree(subject);
  sdsfree(want_before);
  sdsfree(want_after);
}

int main() {
  suite(test_find);
  suite(test_split);
  return report();
}