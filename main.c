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

    struct Neuron *n1 = create_neuron(2);
    struct Neuron *n2 = create_neuron(2);
    struct Neuron *n3 = create_neuron(2);

    struct Value in1 = create_value(2.0, "in1");
    struct Value in2 = create_value(3.0, "in2");
    struct Value in3 = create_value(5.0, "in2");
    struct Value *inputs[] = {&in1, &in2, &in3};

    struct Value in4 = create_value(2.0, "in4");
    struct Value in5 = create_value(3.0, "in5");
    struct Value *inputs2[] = {&in4, &in5};

    // Tests functions.
    test_1(a, b);
    test_2(a, b);
    test_3(x1, x2, w1, w2, bias);
    test_4(x1, x2, w1, w2, bias, z);
    test_5(x1, x2, w1, w2, bias, z, io1);
    test_6(n1, n2, n3, inputs);
    test_7(inputs2);

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
    free_value(&in1);
    free_value(&in2);
    free_value(&in3);
    free_value(&in4);
    free_value(&in5);

    free_neuron(n1);
    free_neuron(n2);
    free_neuron(n3);

    return 0;
}
