#pragma once

#include "sds/sds.h"

// Launches a process with given argc, argv (same as `main`) and
// uses the descriptor provided in out for output
int process_launch(int argc, sds *argv, int out);
