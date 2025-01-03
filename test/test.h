#include <stdio.h>

void expect(int condition, const char *name, const char *message);
void expect_true(int condition, char *name);
void expect_not_null(void *a, char *name);
void expect_null(void *a, char *name);
void expect_eql_int(int a, int b, char *name);

int report();