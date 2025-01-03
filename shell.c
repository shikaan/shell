#include "sds/sds.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NAME "shell"

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

  if (is_error) perror(NAME);

  if (is_child) {
    // execvp expects a NULL terminated array
    argv = sds_realloc(argv, sizeof(sds) * (argc + 1));
    argv[argc] = NULL;
    execvp(argv[0], argv);
    // execvp only returns when there is an error
    perror(NAME);
  }

  int should_wait = 1;
  int status;
  do {
    waitpid(pid, &status, WUNTRACED);
    // Wait for child until it exits or signals
    should_wait = !WIFEXITED(status) && !WIFSIGNALED(status);
  } while (should_wait);

  return 1;
}

void loop(void) {
  int keep_going = 1;

  do {
    printf("$ ");
    int argc = 0;
    sds line = read_line();
    sds *args = sdssplitargs(line, &argc);
    keep_going = launch(argc, args);

    sdsfree(line);
    sdsfreesplitres(args, argc);
  } while (keep_going);
}

int main(int argc, char **argv) {
  loop();
  return EXIT_SUCCESS;
}
