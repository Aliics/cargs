#ifndef CARGS_H
#define CARGS_H

#include "parse.h"

extern void ca_create_flag(char *full_name);

extern void ca_create_str(char *full_name);

extern int ca_get_flag(char *full_name);

extern char *ca_get_str(char *full_name);

#endif
