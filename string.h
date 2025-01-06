#pragma once
#include "sds/sds.h"

// Finds a character in a string and returns its index. 
// If not found, returns -1
int string_find(sds string, char c);

// Splits an sds at given index, returning an array with
// exactly 2 elements: 
// * the first half up to index-1 (included)
// * the second from index (included) till the end
sds *string_split_at(sds string, int index);