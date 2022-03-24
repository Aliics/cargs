#include "cargs.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int args_n;
CA_Arg *args;

int def_args_n;
CA_Arg *def_args;

CA_Arg *get_arg(char *name)
{
    CA_Arg *a;
    for (int i = 0; i < def_args_n; i++)
    {
        if (strcmp(def_args[i].name, name) == 0)
        {
            a = &def_args[i];
            break;
        }
    }

    return a;
}

void add_arg(CA_Arg *ca)
{
    args_n++;
    CA_Arg *tmp = malloc(sizeof(CA_Arg) * args_n);
    memcpy(tmp, args, sizeof(CA_Arg) * (args_n - 1));

    tmp[args_n - 1] = *ca;
    args = tmp;
}

void ca_parse(int argc, char **argv)
{
    for (int i = 0; i < argc; i++)
    {
        char *a = argv[i];
        size_t al = strlen(a);
        if (al < 2)
            continue;

        // A standard argument to be parsed.
        if (a[0] == '-' && a[0] == '-')
        {
            CA_Arg *ca = get_arg(&a[2]);
            if (ca == NULL)
                continue;

            add_arg(ca);
        }
    }
}

void ca_clear_parsed()
{
    args_n = 0;
    def_args_n = 0;
    free(args);
    free(def_args);
}

void ca_create_flag(char *full_name)
{
    // Copy def_args into tmp with +1 size for new arg.
    def_args_n++;
    CA_Arg *tmp = malloc(sizeof(CA_Arg) * def_args_n);
    memcpy(tmp, def_args, sizeof(CA_Arg) * (def_args_n - 1));

    CA_Arg a = {
        .name = full_name,
        .arg_type = CA_ARG_FLAG,
    };
    tmp[def_args_n - 1] = a;
    def_args = tmp;
}

int ca_get_flag(char *full_name)
{
    for (int i = 0; i < args_n; i++)
    {
        if (strcmp(full_name, args[i].name) == 0)
            return 1;
    }

    return 0;
}
