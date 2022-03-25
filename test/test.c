#include "cargs.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void assert(int cond, char *msg)
{
    if (!cond)
    {
        fprintf(stderr, "Test failure: %s\n", msg);
        exit(EXIT_FAILURE);
    }
}

void should_have_defined_flag_when_arg()
{
    ca_clear_parsed();
    char *args[] = {".", "--flag"};
    ca_create_flag("flag");
    int err = ca_parse(2, args);
    assert(err == 0, "an error occurred.");
    assert(ca_get_flag("flag"), "\"flag\" was not set.");
}

void should_not_have_defined_flag_without_arg()
{
    ca_clear_parsed();
    char *args[] = {"."};
    ca_create_flag("flag");
    int err = ca_parse(1, args);
    assert(err == 0, "an error occurred.");
    assert(!ca_get_flag("flag"), "\"flag\" was set.");
}

void should_have_defined_string_arg_when_arg()
{
    ca_clear_parsed();
    char *args[] = {".", "--arg1", "foo"};
    ca_create_str("arg1");
    int err = ca_parse(3, args);
    assert(err == 0, "an error occurred.");
    assert(strcmp(ca_get_str("arg1"), "foo") == 0, "\"arg1\" was not \"foo\".");
}

void should_have_defined_int_arg_when_arg()
{
    ca_clear_parsed();
    char *args[] = {".", "--arg1", "4711"};
    ca_create_int("arg1");
    int err = ca_parse(3, args);
    assert(err == 0, "an error occurred.");
    assert(ca_get_int("arg1") == 4711, "\"arg1\" was not 4711.");
}

void should_fail_when_given_undefined_arg()
{
    ca_clear_parsed();
    char *args[] = {".", "--arg2", "bar"};
    ca_create_str("arg1");
    int err = ca_parse(3, args);
    assert(err != 0, "an error did not occur.");
}

int main(void)
{
    should_have_defined_flag_when_arg();
    should_not_have_defined_flag_without_arg();
    should_have_defined_string_arg_when_arg();
    should_have_defined_int_arg_when_arg();
    should_fail_when_given_undefined_arg();
}
