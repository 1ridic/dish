/*
 * @Author: 1ridic
 * @Date: 2022-09-18 14:13:53
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-20 22:26:59
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

void SIGINT_Handler(int dummy) {
#ifdef DEBUG
  fprintf(stdout,"\ndebug: SIGINT\n");
#endif
  /* Move to a new line */
  fprintf(stdout,"\n");
  /* Regenerate the prompt on a newline */
  rl_on_new_line();
  /* Clear the previous text */
  rl_replace_line("", 0);
  rl_redisplay();
  return;
}

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