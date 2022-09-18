#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "loop.h"
#include "exec.h"

int loop() {
  
  char *line;
  char **args;
  int status = 1;
  printf("> ");
  line = readLine();
  args = splitLine(line);
  status = forkExec(args);
  free(line);
  free(args);
  return 0;
}