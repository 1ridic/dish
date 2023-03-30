/*
 * @Author: 1ridic
 * @Date: 2022-09-18 14:13:53
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-20 22:26:59
 */
#include "loop.h"
#include "exec.h"
#include "line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

int status;

void SIGINT_Handler(int dummy) {
#ifdef DEBUG
  fprintf(stdout, "\ndebug: SIGINT\n");
#endif
  /* Move to a new line */
  fprintf(stdout, "\n");
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
  line = readline(ANSI_COLOR_GREEN "> " ANSI_COLOR_RESET);
  add_history(line);
  args = splitLine(line);
  if (args == NULL) {
    free(line);
    free(args);
    return 1;
  }
  status = commandExec(args);
  free(line);
  /*free all array in args*/
  for (int i = 0; args[i] != NULL; i++) {
    free(args[i]);
  }
  free(args);
  return 0;
}