/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:16:19 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 14:28:01
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int dish_cd(char **args);
int dish_help(char **args);
int dish_exit(char **args);

char* builtin_cmd[] = {
  "cd",
  "help",
  "exit"
};

int (*builtin_func[]) (char **) = {
  &dish_cd,
  &dish_help,
  &dish_exit
};

int dish_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "dish: expected argument to \"cd\"\n");
  } else {
    if (chdir(args[1]) != 0) {
      perror("dish");
    }
  }
  return 0;
}

int dish_help(char **args)
{
   fprintf(stdout, "Yet another Shell with C.\n");
   return 0;
}

int dish_exit(char **args)
{
  exit(EXIT_SUCCESS);
}

int getBuiltinNum() {
  return sizeof(builtin_cmd) / sizeof(char *);
}