#ifndef CARGS_H
#define CARGS_H

#include "parse.h"

extern void ca_create_flag(char *name);

extern void ca_create_str(char *name);

extern void ca_create_int(char *name);

extern int ca_get_flag(char *name);

extern char *ca_get_str(char *name);

extern int ca_get_int(char *name);

#endif
