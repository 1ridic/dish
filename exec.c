/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:14:23 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 14:44:37
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include "builtin.h"

extern int (*builtin_func[]) (char **);
extern char* builtin_cmd[];

int forkExec(char **args) {
  pid_t pid;
  int status;
#ifdef DEBUG
    printf("debug: fork enter.\n");
#endif
  pid = fork();
  if (pid == 0) { 
    /* child process */
      if (execvp(args[0], args) == -1) {
        perror("dish");
        exit(EXIT_FAILURE);
      }
  } else if (pid < 0) {
    /* fork error */
    perror("dish");
  } else {
    extern char volatile isWaiting;
    isWaiting = 1;
    /* parent process: wait child process*/
    pid=wait(&status);
    isWaiting = 0;
    
  }
  return WEXITSTATUS(status);
}

int commandExec(char **args) {
  int i;

  if (args[0] == NULL) {
    /* empty command */
    return 1;
  }

  for (i = 0; i < getBuiltinNum(); i++) {
    if (strcmp(args[0], builtin_cmd[i]) == 0) {
      return (*builtin_func[i])(args);
    }
  }

  return forkExec(args);
}
