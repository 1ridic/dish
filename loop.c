/*
 * @Author: 1ridic
 * @Date: 2022-09-18 14:13:53
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 23:32:02
 */
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <string.h>
#include "loop.h"
#include "exec.h"
#include "line.h"

int status;

int loop() {

  char *line;
  char **args;
  line = readline(ANSI_COLOR_GREEN"> "ANSI_COLOR_RESET);
  add_history(line);
  args = splitLine(line);
  status = commandExec(args);
  free(line);
  free(args);
  return 0;
}