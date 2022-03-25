#ifndef CARGS_PARSE_H
#define CARGS_PARSE_H

typedef enum
{
    CA_ARG_FLAG,
    CA_ARG_STR,
    CA_ARG_INT,
}
CA_ArgType;

typedef struct
{
    char *name;
    char short_name;
    CA_ArgType arg_type;
} CA_DefArg;

typedef struct
{
    CA_DefArg def_arg;
    char *value;
} CA_Arg;

extern int ca_parse(int argc, char **argv);

extern void ca_clear_parsed();

extern int ca_args_n;
extern CA_Arg *ca_args;

extern int ca_def_args_n;
extern CA_DefArg *ca_def_args;

#endif
