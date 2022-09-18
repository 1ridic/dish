/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:13:59 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 22:01:12
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include "loop.h"

char volatile isWaiting = 0; 
void intHandler(int dummy) {
#ifdef DEBUG
  fprintf(stdout,"\ndebug: enter soft-irq. isWaiting=%d\n",isWaiting);
#endif
  if (isWaiting==1) {
    return;
  }
  extern FILE* hf;
  fprintf(stderr,"\nSIGINT exit.");
  fclose(hf);
  exit(EXIT_FAILURE);
  
}

int main(int argc, char *argv[]) {
  /* soft irq */
  signal(SIGINT, intHandler);
  /* clear screen */
  fprintf(stdout,"\033[H\033[J");
  /* open history file */
  extern FILE* hf;
  hf = fopen(strcat(getenv("HOME"), "/.dish_history"), "w");
  
#ifdef DEBUG
  fprintf(stdout,"DEBUG is defined\n");
#endif
  while (1) {
    loop();
  }
  
  fclose(hf);
  return 0;
}