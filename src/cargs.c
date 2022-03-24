#include "cargs.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int args_n;
CA_Arg *args;

int def_args_n;
CA_DefArg *def_args;

CA_DefArg *get_def_arg(char *name)
{
    CA_DefArg *a;
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

void add_arg(CA_Arg ca)
{
    args_n++;
    CA_Arg *tmp = malloc(sizeof(CA_Arg) * args_n);
    memcpy(tmp, args, sizeof(CA_Arg) * (args_n - 1));

    tmp[args_n - 1] = ca;
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
        if (a[0] == '-' && a[1] == '-')
        {
            CA_DefArg *cda = get_def_arg(&a[2]);
            if (cda == NULL)
                continue;

            CA_DefArg cda_copy = {
                .name = cda->name,
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
                ca.value = malloc(sizeof(char) * strlen(argv[i++]));
                strcpy(ca.value, argv[i++]);
                break;
            }

            add_arg(ca);
        }
    }
}

void ca_clear_parsed()
{
    if (def_args_n != 0)
        free(def_args);  
    if (args_n != 0)
        free(args);
    args_n = 0;
    def_args_n = 0;
}

void ca_create_arg(char *full_name, CA_ArgType arg_type)
{
    // Copy def_args into tmp with +1 size for new arg.
    def_args_n++;
    CA_DefArg *tmp = malloc(sizeof(CA_DefArg) * def_args_n);
    memcpy(tmp, def_args, sizeof(CA_DefArg) * (def_args_n - 1));

    CA_DefArg a = {
        .name = full_name,
        .arg_type = arg_type,
    };
    tmp[def_args_n - 1] = a;
    def_args = tmp;
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
    for (int i = 0; i < args_n; i++)
    {
        if (strcmp(full_name, args[i].def_arg.name) == 0)
            return 1;
    }

    return 0;
}

char *ca_get_str(char *full_name)
{
    for (int i = 0; i < args_n; i++)
    {
        if (strcmp(full_name, args[i].def_arg.name) == 0)
            return args[i].value;
    }

    return NULL;
}
