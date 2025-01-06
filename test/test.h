#include <stdio.h>

void expect(int condition, const char *name, const char *message);
void expect_true(int condition, const char *name);
void expect_not_null(void *a, const char *name);
void expect_null(void *a, const char *name);
void expect_eql_int(int a, int b, const char *name);

#define case(name) printf("  %s:\n", name)

#define suite(name) {\
  printf("\n> %s\n", #name);\
  name();\
}

int report();