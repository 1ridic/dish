/*
 * @Author: 1ridic
 * @Date: 2022-09-18 14:16:19
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 23:32:50
 */
#include "builtin.h"
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <unistd.h>

int dish_cd(char **args);
int dish_help(char **args);
int dish_exit(char **args);
int dish_clear(char **args);
int dish_setenv(char **args);
int dish_getenv(char **args);
int dish_unsetenv(char **args);
int dish_echo(char **args);
int dish_laststatus(char **args);

char *builtin_cmd[] = {"cd",     "help",     "exit", "clear",     "setenv",
                       "getenv", "unsetenv", "echo", "laststatus", defined_builtin};

int (*builtin_func[])(char **) = {
    &dish_cd,     &dish_help,     &dish_exit, &dish_clear,     &dish_setenv,
    &dish_getenv, &dish_unsetenv, &dish_echo, &dish_laststatus, defined_builtin_func};

int getBuiltinNum() { return sizeof(builtin_cmd) / sizeof(char *); }

int dish_cd(char **args) {
  if (args[1] == NULL) {
    fprintf(stderr, "dish: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("dish");
    }
  }
  return 0;
}

int dish_help(char **args) {
  fprintf(stdout, "Yet another Shell with C.\n");
  return 0;
}

int dish_exit(char **args) { exit(EXIT_SUCCESS); }

int dish_clear(char **args) {
  fprintf(stdout, "\033[H\033[J");
  return 0;
}

int dish_setenv(char **args) {
  if (args[1] == NULL || args[2] == NULL) {
    fprintf(stderr, "dish: expected 2 arguments to \"setenv\"\n");
    return 1;
  }

  setenv(args[1], args[2], 1);
  return 0;
}

int dish_getenv(char **args) {
  fprintf(stdout, "%s\n", getenv(args[1]));
  return 0;
}

int dish_unsetenv(char **args) {
  long i = 1;
  while (args[i] != NULL) {
    unsetenv(args[i]);
    i++;
  }
  return 0;
}

int dish_echo(char **args) {
  if (args[1][0] == '$') {
    char *env = getenv(args[1] + sizeof(char));
    if (env != NULL)
      fprintf(stdout, "%s\n", env);
  } else
    fprintf(stdout, "%s\n", args[1]);
  return 0;
}

int dish_laststatus(char **args) {
  extern int status;
  fprintf(stdout, "%d\n", status);
  return 0;
}