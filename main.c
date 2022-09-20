/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:13:59 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-20 22:23:59
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "loop.h"


int main(int argc, char *argv[]) {
  /* soft irq */
  signal(SIGINT, SIGINT_Handler);
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
