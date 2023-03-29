/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 20:29:12 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 20:29:55
 */
#ifndef _CONFIG_H_
#define _CONFIG_H_

#define LINE_BUF_SIZE 1024

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* enable postgres support*/
#define POSTGRES
#ifdef POSTGRES
#define defined_builtin "pg"
#define defined_builtin_func &dish_pg
#endif

#endif