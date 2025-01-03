#include "sds/sds.h"

typedef enum {
  BUILTIN_CD = 100,
  BUILTIN_EXIT,
  BUILTIN_UNDEFINED = -1
} Builtin;

// Returns a builtin from a raw string. It returns BUILTIN_UNDEFINED when none
// is found.
Builtin builtin_from(sds raw);

// Execute the builtin. Returns 0 when shell execution should stop
int builtin_launch(Builtin builtin, int argc, sds *argv);
