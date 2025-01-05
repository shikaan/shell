#include "builtin.h"
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

int launch(int argc, sds *argv) {
  pid_t pid;

  pid = fork();
  const int is_error = pid < 0;
  const int is_child = pid == 0;

  if (is_error)
    perror(NAME);

  if (is_child) {
    // execvp expects a NULL terminated array
    argv = sds_realloc(argv, sizeof(sds) * (argc + 1));
    argv[argc] = NULL;
    execvp(argv[0], argv);
    // execvp only returns when there is an error
    perror(NAME);
    exit(EXIT_FAILURE);
  }

  int should_wait = 1, status = 0;
  do {
    waitpid(pid, &status, WUNTRACED);
    // Wait for child until it exits or signals
    should_wait = !WIFEXITED(status) && !WIFSIGNALED(status);
  } while (should_wait);

  return status;
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
        status = launch(argc, argv);
      } else {
        status = builtin_launch(b, argc, argv);
      }
    }

    sdsfree(line);
    sdsfreesplitres(argv, argc);
  }

  return status;
}
