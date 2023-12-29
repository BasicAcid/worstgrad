#include <stdio.h>
#include <string.h>
#include "main.h"

int
main(void)
{

    struct Value a = create_value(-2, "a");
    struct Value b = create_value(3, "b");

    test_1(a, b);


    return 0;
}
