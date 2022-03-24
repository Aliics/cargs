#ifndef CARGS_H
#define CARGS_H

typedef enum
{
    CA_ARG_FLAG,
}
CA_ArgType;

typedef struct
{
    char *name;
    CA_ArgType arg_type;
} CA_Arg;

extern void ca_parse(int argc, char **argv);

extern void ca_create_flag(char *full_name);

extern int ca_get_flag(char *full_name);

#endif
