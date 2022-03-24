#include "cargs.h"
#include "parse.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

void ca_create_arg(char *full_name, CA_ArgType arg_type)
{
    // Copy ca_def_args into tmp with +1 size for new arg.
    ca_def_args_n++;
    CA_DefArg *tmp = malloc(sizeof(CA_DefArg) * ca_def_args_n);
    memcpy(tmp, ca_def_args, sizeof(CA_DefArg) * (ca_def_args_n - 1));

    CA_DefArg a = {
        .name = full_name,
        .arg_type = arg_type,
    };
    tmp[ca_def_args_n - 1] = a;
    ca_def_args = tmp;
}

void ca_create_flag(char *full_name)
{
    ca_create_arg(full_name, CA_ARG_FLAG);
}

void ca_create_str(char *full_name)
{
    ca_create_arg(full_name, CA_ARG_STR);
}

int ca_get_flag(char *full_name)
{
    for (int i = 0; i < ca_args_n; i++)
    {
        if (strcmp(full_name, ca_args[i].def_arg.name) == 0)
            return 1;
    }

    return 0;
}

char *ca_get_str(char *full_name)
{
    for (int i = 0; i < ca_args_n; i++)
    {
        if (strcmp(full_name, ca_args[i].def_arg.name) == 0)
            return ca_args[i].value;
    }

    return NULL;
}
