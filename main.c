#include <stdio.h>
#include <signal.h>

int main(int argc, char *argv[]) {
    printf("Hello, World!");
    #ifdef DEBUG
    printf("DEBUG is defined");
    #endif
    return 0;
}