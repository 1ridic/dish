/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:13:59 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 14:53:04
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "loop.h"

char volatile isWaiting = 0; 
void intHandler(int dummy) {
  if (isWaiting) {
    return;
  fprintf(stderr,"\nSIGINT exit.\n");
  exit(EXIT_FAILURE);
  }
}

int main(int argc, char *argv[]) {
  /* soft irq */
  signal(SIGINT, intHandler);
  /* clear screen */
  fprintf(stdout,"\033[H\033[J");
#ifdef DEBUG
  fprintf(stdout,"DEBUG is defined\n");
#endif
  while (1) {
    loop();
  }
  return 0;
}