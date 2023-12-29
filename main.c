#include <stdio.h>
#include <string.h>
#include "main.h"

int
main(void)
{

    struct Value a = create_value(-2, "a");
    struct Value b = create_value(3, "b");
    struct Value d = w_sub(&a, &b, "d");
    struct Value g = w_tanh(&d, "g");

    test_1(a, b, d, g);


    return 0;
}
