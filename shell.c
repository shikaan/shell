#include "builtin.h"
#include "process.h"
#include "utils.h"
#include "string.h"

#include "sds/sds.h"

#include <fcntl.h>
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

const char OUTPUT_REDIRECT = '>';
const char* CLEANUP_CHARS = " >";
sds *parse_line(sds line, int *argc, int *out) {
  const int line_length = sdslen(line);
  int redirect_index = string_find(line, OUTPUT_REDIRECT);

  // There is no redirect symbol, send output to STDOUT
  if (redirect_index == -1) {
    sds *argv = sdssplitargs(line, argc);
    *out = STDOUT_FILENO;
    return argv;
  }

  sds *split = string_split_at(line, redirect_index);

  split[1] = sdstrim(split[1], CLEANUP_CHARS);
  *out = open(split[1], O_RDWR | O_CREAT | O_TRUNC, 0666);
  if (*out == -1)
    goto error;

  split[0] = sdstrim(split[0], CLEANUP_CHARS);
  sds *argv = sdssplitargs(split[0], argc);
  sdsfreesplitres(split, 2);
  return argv;

error:
  perror(NAME);
  sdsfreesplitres(split, 2);
  return NULL;
}

int main(int argc, char **argv) {
  int status = 0;

  while (1) {
    printf(PROMPT);
    sds line = read_line();
    int argc = 0, out = STDOUT_FILENO;
    sds *argv = parse_line(line, &argc, &out);

    if (argv && argc != 0) {
      Builtin b = builtin_from(argv[0]);

      if (b == BUILTIN_UNDEFINED) {
        status = process_launch(argc, argv, out);
      } else {
        status = builtin_launch(b, argc, argv);
      }
    }

    sdsfree(line);
    sdsfreesplitres(argv, argc);
  }

  return status;
}
