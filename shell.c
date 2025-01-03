#include "sds/sds.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

int launch(sds *args) {
  pid_t pid;

  pid = fork();
  const int is_error = pid < 0;
  const int is_child = pid == 0;

  if (is_error) {
    perror("shell: fork error");
  }

  if (is_child) {
    execvp(args[0], args);
    perror("shell: exec error");
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
    sds *sds_args = sdssplitargs(line, &argc);
    sdsfree(line);

    char **args = malloc(sizeof(sds) * (argc + 1));
    for (int i = 0; i < argc; i++) {
      args[i] = sds_args[i];
    }
    args[argc] = NULL;

    keep_going = launch(args);
    sdsfreesplitres(sds_args, argc);
  } while (keep_going);
}

int main(int argc, char **argv) {
  loop();
  return EXIT_SUCCESS;
}
