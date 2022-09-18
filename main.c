#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static volatile int keepRunning = 1;

void intHandler(int dummy) {
  printf("\nend!\n");
  keepRunning = 0;
}

int main(int argc, char *argv[]) {

  signal(SIGINT, intHandler);

  printf("Hello, World!\n");
#ifdef DEBUG
  printf("DEBUG is defined\n");
#endif
  while (keepRunning) {
    printf("runing!\n");
    sleep(1);
  }
  return 0;
}