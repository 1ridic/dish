#include "line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *readLine(void) {
  int bufsize = LINE_BUF_SIZE;
  int position = 0;
  char *buffer = malloc(sizeof(char) * bufsize);
  char c;

  if (!buffer) {
    fprintf(stderr, "dish: allocation error\n");
    exit(EXIT_FAILURE);
  }

  while (1) {
    // read a character
    c = getchar();
    // repleace EOF with a null character and return
    if (c == EOF || c == '\n') {
      buffer[position] = '\0';
      return buffer;
    } else {
      buffer[position] = c;
    }
    position++;

    /* if the buffer is full, reallocate */
    if (position >= bufsize) {
      bufsize += LINE_BUF_SIZE;
      buffer = realloc(buffer, bufsize);
      if (!buffer) {
        fprintf(stderr, "dish: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }
  }
}

char **splitLine(char *line) {
  int bufsize = LINE_BUF_SIZE, position = 0;
  char **tokens = malloc(bufsize * sizeof(char *));
  char *token;

  if (!tokens) {
    fprintf(stderr, "dish: allocation error");
    exit(EXIT_FAILURE);
  }

  /* get sub string
   *" \t\r\n\a" is a set of delimiters,
   * which stands for space, tab, carriage, newline, and alert.
   */
  token = strtok(line, " \t\r\n\a");

  while (token != NULL) {
    tokens[position] = token;
#ifdef DEBUG
    fprintf(stdout, "debug: tokens[%d] = %s\n", position, tokens[position]);
#endif
    position++;

    /* if the buffer is full, reallocate */
    if (position >= bufsize) {
      bufsize += LINE_BUF_SIZE;
      tokens = realloc(tokens, bufsize);
      if (!tokens) {
        fprintf(stderr, "dish: allocation error\n");
        exit(EXIT_FAILURE);
      }
    }

    token = strtok(NULL, " \t\r\n\a");
  }

  /* set the last element to NULL */
  tokens[position] = NULL;
  return tokens;
}
