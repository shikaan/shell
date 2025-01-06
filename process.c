#include "process.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef int fildes;

fildes stdout_ref = STDOUT_FILENO;
void restore_stdout() {
  dup2(stdout_ref, STDOUT_FILENO);  
}

int process_launch(int argc, sds *argv, fildes out) {
  const pid_t pid = fork();
  const int is_error = pid < 0;
  const int is_child = pid == 0;

  if (is_error)
    perror(NAME);

  if (is_child) {
    // execvp expects a NULL terminated array
    argv = sds_realloc(argv, sizeof(sds) * (argc + 1));
    argv[argc] = NULL;

    // prepare output redirection
    atexit(restore_stdout);

    if (dup2(out, STDOUT_FILENO) == -1) {
      perror(NAME);
      exit(EXIT_FAILURE);
    }
    
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
