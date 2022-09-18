/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:14:28 
 * @Last Modified by:   1ridic 
 * @Last Modified time: 2022-09-18 14:14:28 
 */
#ifndef _LINE_H_
#define _LINE_H_
#define LINE_BUF_SIZE 1024

char *readLine(void);
char **splitLine(char *line);
#endif