#include "cargs.h"
#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void ca_create_arg(char *name, CA_ArgType arg_type)
{
    // Copy ca_def_args into tmp with +1 size for new arg.
    CA_DefArg *tmp = malloc(sizeof(CA_DefArg) * (ca_def_args_n + 1));
    if (ca_def_args_n > 0)
        memcpy(tmp, ca_def_args, sizeof(CA_DefArg) * ca_def_args_n);

    if (ca_def_args_n > 0)
        free(ca_def_args);

    CA_DefArg a = {
        .name = name,
        .arg_type = arg_type,
    };
    tmp[ca_def_args_n] = a;
    ca_def_args = tmp;
    ca_def_args_n++;
}

void ca_create_flag(char *name)
{
    ca_create_arg(name, CA_ARG_FLAG);
}

void ca_create_str(char *name)
{
    ca_create_arg(name, CA_ARG_STR);
}


void ca_create_int(char *name)
{
    ca_create_arg(name, CA_ARG_INT);
}

int ca_get_flag(char *name)
{
    for (int i = 0; i < ca_args_n; i++)
    {
        if (strcmp(name, ca_args[i].def_arg.name) == 0)
            return 1;
    }

    return 0;
}

char *ca_get_str(char *name)
{
    for (int i = 0; i < ca_args_n; i++)
    {
        if (strcmp(name, ca_args[i].def_arg.name) == 0)
            return ca_args[i].value;
    }

    return NULL;
}

int ca_get_int(char *name)
{
    for (int i = 0; i < ca_args_n; i++)
    {
        if (strcmp(name, ca_args[i].def_arg.name) == 0)
            return atoi(ca_args[i].value);
    }

    return -1;
}
