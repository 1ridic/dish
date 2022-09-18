#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

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
    /* parent process: wait child process*/
    pid=wait(&status);
    
  }
  return WEXITSTATUS(status);
}
