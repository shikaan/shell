#include "sds/sds.h"
#include <stdio.h>
#include <stdlib.h>

sds read_line() {
  char c;
  sds line = sdsempty();
  
  while (1) {
    c = getchar();
    if (c == EOF || c == '\n') return line;
    line = sdscatprintf(line, "%c", c);
  }
}

void loop(void) {
  int status = 1;

  do {
    printf("$ ");
    int argc = 0;
    sds line = read_line();
    sds *args = sdssplitargs(line, &argc);
    // TODO: execute command

    sdsfree(line);
    sdsfreesplitres(args, argc);
  } while (status);
}

int main(int argc, char **argv) {
  loop();
  return EXIT_SUCCESS;
}
