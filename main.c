/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:13:59 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 23:21:37
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
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
  const char* hf_path=strcat(getenv("HOME"), "/.dish_history");
  hf = fopen(hf_path, "a+");
  
#ifdef DEBUG
  fprintf(stdout,"DEBUG is defined\n");
#endif
  while (1) {
    loop();
  }
  
  fclose(hf);
  return 0;
}