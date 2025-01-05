#include "builtin.h"
#include "process.h"
#include "utils.h"

#include "sds/sds.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PROMPT "$ "

sds read_line() {
  char c;
  sds line = sdsempty();

  while (1) {
    c = getchar();
    if (c == EOF || c == '\n')
      return line;
    line = sdscatprintf(line, "%c", c);
  }
}

int main(int argc, char **argv) {
  int status = 0;

   while (1) {
    printf(PROMPT);
    sds line = read_line();

    int argc = 0;
    sds *argv = sdssplitargs(line, &argc);
    if (argc != 0) {
      Builtin b = builtin_from(argv[0]);

      if (b == BUILTIN_UNDEFINED) {
        status = process_launch(argc, argv);
      } else {
        status = builtin_launch(b, argc, argv);
      }
    }

    sdsfree(line);
    sdsfreesplitres(argv, argc);
  }

  return status;
}
