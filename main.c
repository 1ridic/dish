#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "loop.h"

void intHandler(int dummy) {
  printf("\nSIGINT exit.\n");
  exit(EXIT_FAILURE);
}

int main(int argc, char *argv[]) {

  signal(SIGINT, intHandler);

#ifdef DEBUG
  printf("DEBUG is defined\n");
#endif
  while (1) {
    loop();
  }
  return 0;
}