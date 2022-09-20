/*
 * @Author: 1ridic
 * @Date: 2022-09-18 14:13:53
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 23:32:02
 */
#include "loop.h"
#include "exec.h"
#include "line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int status;

int loop() {

  char *line;
  char **args;
  printf(ANSI_COLOR_GREEN"> "ANSI_COLOR_RESET);
  line = readLine();
  args = splitLine(line);
  status = commandExec(args);
  free(line);
  free(args);
  return 0;
}