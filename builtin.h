/*
 * @Author: 1ridic 
 * @Date: 2022-09-18 14:15:44 
 * @Last Modified by: 1ridic
 * @Last Modified time: 2022-09-18 20:31:59
 */
#ifndef _BUILTIN_H_
#define _BUILTIN_H_

#include "config.h"

#ifdef POSTGRES
#include "postgres.h"
#endif

int getBuiltinNum();

#endif