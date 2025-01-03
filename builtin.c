#include "builtin.h"
#include "utils.h"

#include "sds/sds.h"

#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define CD_STRING "cd"
#define EXIT_STRING "exit"

sds get_home() {
  char *home = getenv("HOME");
  if (home == NULL) {
    home = getpwuid(getuid())->pw_dir;
  }
  return sdsnew(home);
}

int builtin_cd(int argc, sds *argv) {
  if (argc <= 1) {
    sds directory = get_home();
    if (chdir(directory) != 0)
      perror(NAME);
    sdsfree(directory);
    return 1;
  }

  if (chdir(argv[1]) != 0)
    perror(NAME);
  return 1;
}

int builtin_exit(int argc, sds *argv) {
  UNUSED(argc);
  UNUSED(argv);
  return 0;
}

Builtin builtin_from(const sds raw) {
  sds other = sdsempty();

  other = sdscpy(other, CD_STRING);
  if (sdscmp(raw, other) == 0)
    return BUILTIN_CD;

  other = sdscpy(other, EXIT_STRING);
  if (sdscmp(raw, other) == 0)
    return BUILTIN_EXIT;

  sdsfree(other);
  return BUILTIN_UNDEFINED;
}

int builtin_launch(Builtin builtin, int argc, sds *argv) {
  switch (builtin) {
  case BUILTIN_CD:
    return builtin_cd(argc, argv);
  case BUILTIN_EXIT:
    return builtin_exit(argc, argv);
  default:
    return -1;
  }
}