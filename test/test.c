#include <stdio.h>

int testCount = 0;
int failedCount = 0;

void expect(int condition, const char *name, const char *message) {
  testCount++;
  if (!condition) {
    failedCount++;
    printf("  fail - %s: %s\n", name, message);
    return;
  }
  printf("   ok  - %s\n", name);
}

void expect_true(int condition, char *name) {
  expect(condition, name, "Expected value to be true");
}

void expect_not_null(void *a, char *name) {
  expect(a != NULL, name, "Expected value not to be null");
}

void expect_null(void *a, char *name) {
  expect(a == NULL, name, "Expected value to be null");
}

void expect_eql_int(int a, int b, char *name) {
  char msg[256];
  snprintf(msg, 256, "Expected %d to equal %d", a, b);
  expect(a == b, name, msg);
}

int report() {
  printf("\n%d assertions, %d failed\n", testCount, failedCount);
  return failedCount;
}