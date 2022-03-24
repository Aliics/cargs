#include "cargs.h"
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    char *args[] = {".", "--flag"};
    ca_create_flag("flag");
    ca_parse(2, args);

    if (!ca_get_flag("flag"))
    {
        fprintf(stderr, "Test failure: \"flag\" was not set.\n");
        exit(EXIT_FAILURE);
    }
}
