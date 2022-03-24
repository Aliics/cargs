#include "cargs.h"
#include <stdio.h>
#include <stdlib.h>

void should_have_defined_flag_when_arg()
{
    ca_clear_parsed();
    char *args[] = {".", "--flag"};
    ca_create_flag("flag");
    ca_parse(2, args);

    if (!ca_get_flag("flag"))
    {
        fprintf(stderr, "Test failure: \"flag\" was not set.\n");
        exit(EXIT_FAILURE);
    }
}

void should_not_have_defined_flag_without_arg()
{
    ca_clear_parsed();
    char *args[] = {"."};
    ca_create_flag("flag");
    ca_parse(1, args);

    if (ca_get_flag("flag"))
    {
        fprintf(stderr, "Test failure: \"flag\" was set.\n");
        exit(EXIT_FAILURE);
    }
}

int main(void)
{
    should_have_defined_flag_when_arg();
    should_not_have_defined_flag_without_arg();
}
