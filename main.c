#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "line.h"


void intHandler(int dummy) {
  printf("\nend!\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

  signal(SIGINT, intHandler);

  printf("Hello, World!\n");
#ifdef DEBUG
  printf("DEBUG is defined\n");
#endif
  while (1) {
    printf("runing!\n");
    sleep(1);
  }
  return 0;
}