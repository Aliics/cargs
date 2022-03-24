#include "cargs.h"

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

int args_n;
CA_Arg *args;

void ca_parse(int argc, char **argv) 
{
    // todo: implement
}

void ca_create_flag(char *full_name)
{
    // Copy args into tmp with +1 size for new arg.
    args_n++;
    CA_Arg *tmp = malloc(sizeof(CA_Arg) * args_n);
    memcpy(tmp, args, sizeof(char *) * (args_n - 1));

    CA_Arg a = {
        .name = full_name,
        .arg_type = CA_ARG_FLAG
    };
    tmp[args_n - 1] = a;
    args = tmp;
}

int ca_get_flag(char *full_name)
{
    // todo: implement
    return 0;
}
