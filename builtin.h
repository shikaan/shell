#include "sds/sds.h"

typedef enum {
  BUILTIN_CD = 100,
  BUILTIN_EXIT,
  BUILTIN_UNDEFINED = -1
} Builtin;

// Returns a builtin from a string or `BUILTIN_UNDEFINED` when none is found.
Builtin builtin_from(sds raw);

// Executes a given builtin and returns its status code from execution
int builtin_launch(Builtin builtin, int argc, sds *argv);
