/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:13:53 
 * @Last Modified by:   1ridic 
 * @Last Modified time: 2022-09-18 14:13:53 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "line.h"
#include "loop.h"
#include "exec.h"

int loop() {
  
  char *line;
  char **args;
  printf("> ");
  line = readLine();
  args = splitLine(line);
  commandExec(args);
  free(line);
  free(args);
  return 0;
}