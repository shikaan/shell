#include "string.h"
#include "sds/sds.h"

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

// Finds a character in a string and returns its index.
// If not found, returns -1
int string_find(sds string, char c) {
  for (int i = 0; i < (int)sdslen(string); i++) {
    if (string[i] == c)
      return i;
  }
  return -1;
}

// Splits an sds at given index, returning an array with
// exactly 2 elements:
// * the first half up to index-1 (included)
// * the second from index (included) till the end
sds *string_split_at(sds string, int index) {
  sds *result = (sds *)sds_malloc(sizeof(char *) * 2);

  if (index <= 0) {
    result[0] = sdsempty();
    result[1] = sdsdup(string);
    return result;
  }

  if (index >= (int)sdslen(string)) {
    result[0] = sdsdup(string);
    result[1] = sdsempty();
    return result;
  }

  result[0] = sdsdup(string);
  sdsrange(result[0], 0, max(index - 1, 0));

  int len = sdslen(string);
  result[1] = sdsdup(string);
  sdsrange(result[1], min(index, len), len);

  return result;
}
