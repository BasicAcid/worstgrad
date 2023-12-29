#include <stdio.h>
#include <string.h>
#include "main.h"

int
main(void)
{
    // Some values.
    struct Value a = create_value(-2, "a");
    struct Value b = create_value(3, "b");
    struct Value x1 = create_value(2.0, "x1");
    struct Value x2 = create_value(0.0, "x2");
    struct Value w1 = create_value(-3.0, "w1");
    struct Value w2 = create_value(1.0, "w2");
    struct Value bias = create_value(6.8813735870195432, "b");
    struct Value z = create_value(2.0, "z");
    struct Value io1 = create_value(1.0, "io1");

    // Tests functions.
    test_1(a, b);
    test_2(a, b);
    test_3(x1, x2, w1, w2, bias);
    test_4(x1, x2, w1, w2, bias, z);
    test_5(x1, x2, w1, w2, bias, z, io1);

    // Free memory.
    free_value(&a);
    free_value(&b);
    free_value(&x1);
    free_value(&x2);
    free_value(&w1);
    free_value(&w2);
    free_value(&bias);
    free_value(&z);
    free_value(&io1);

    return 0;
}
