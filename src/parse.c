#include "parse.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int ca_args_n;
CA_Arg *ca_args;

int ca_def_args_n;
CA_DefArg *ca_def_args;

CA_DefArg *get_def_arg_full(char *name)
{
    CA_DefArg *a = NULL;
    for (int i = 0; i < ca_def_args_n; i++)
    {
        if (strcmp(ca_def_args[i].name, name) == 0)
        {
            a = &ca_def_args[i];
            break;
        }
    }

    return a;
}

CA_DefArg *get_def_arg_short(char c)
{
    CA_DefArg *a = NULL;
    for (int i = 0; i < ca_def_args_n; i++)
    {
        if (ca_def_args[i].short_name == c)
        {
            a = &ca_def_args[i];
            break;
        }
    }

    return a;
}

void add_arg(CA_Arg ca)
{
    CA_Arg *tmp = malloc(sizeof(CA_Arg) * (ca_args_n + 1));
    if (ca_args_n > 0)
        memcpy(tmp, ca_args, sizeof(CA_Arg) * ca_args_n);

    if (ca_args_n > 1)
        free(ca_args);

    tmp[ca_args_n] = ca;
    ca_args = tmp;
    ca_args_n++;
}

int ca_parse(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        char *a = argv[i];
        size_t al = strlen(a);
        if (al < 2)
            continue;

        // A standard argument to be parsed.
        if (a[0] == '-')
        {
            CA_DefArg *cda = a[1] == '-' ? get_def_arg_full(&a[2]) : get_def_arg_short(a[1]);
            if (cda == NULL)
                return -1;

            CA_DefArg cda_copy = {
                .name = cda->name,
                .short_name = cda->short_name,
                .arg_type = cda->arg_type,
            };
            CA_Arg ca;
            ca.def_arg = cda_copy;
            switch (cda->arg_type)
            {
            case CA_ARG_FLAG:
                ca.value = "";
                break;
            case CA_ARG_STR:
            case CA_ARG_INT:
                ca.value = malloc(sizeof(char) * strlen(argv[i++]));
                strcpy(ca.value, argv[i++]);
                break;
            }

            add_arg(ca);
        }
    }

    return 0;
}

void ca_clear_parsed()
{
    if (ca_def_args_n > 0)
        free(ca_def_args);
    if (ca_args_n > 0)
        free(ca_args);
    ca_args_n = 0;
    ca_def_args_n = 0;
}
