/*
 * @Author: 1ridic
 * @Date: 2022-09-18 14:14:05
 * @Last Modified by:   1ridic
 * @Last Modified time: 2022-09-18 14:14:05
 */
#include "line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>


/*split one line to word, when appears "", save the content to one word*/
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
    /*detect if there exists "" pair*/
    if (token[0] == '"') {
      char *temp = malloc(bufsize * sizeof(char *));
      for (int i = 0; i < strlen(token); i++) {
        /*delete the first " */
        temp[i] = token[i + 1];
      }
      /*read next token and detect " */
      int pair_flag = 0;
      while (1) {
        token = strtok(NULL, " \t\r\n\a");
        if (token[strlen(token) - 1] == '"') {
          /*delete the last " */
          token[strlen(token) - 1] = '\0';
          strcat(temp, " ");
          strcat(temp, token);
          token=temp;
          break;
        } else {
          strcat(temp, " ");
          strcat(temp, token);
          pair_flag = 1;
        }
        if(token==NULL&&pair_flag==0){
          fprintf(stderr,"error: no pair \"\n");
          return NULL;
        }
      }
    }
    else
    {
      char* temp=malloc(bufsize * sizeof(char *));
      strcpy(temp,token);
      token=temp;
    }
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
