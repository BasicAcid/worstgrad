#include <stdio.h>
#include <string.h>
#include "main.h"

void
test_1(struct Value a, struct Value b)
{
    struct Value d = w_sub(&a, &b, "d");
    struct Value g = w_tanh(&d, "g");

    g.grad = 1.0;

    struct Stack stack;

    // Find a way to automate this.
    int initial_capacity = 100;
    init_stack(&stack, initial_capacity);

    dfs_to_stack(&g, &stack);

    double h = 0.001;

    grandient_descent(&stack, h, 100);

    backward_stack(&stack);

    print_stack(&stack);

    cleanup_stack(&stack);

    free_value(&d);
    free_value(&g);
}

void
test_2(struct Value a, struct Value b)
{
    struct Value c = w_mul(&a, &b, "c");
    struct Value g = w_tanh(&c, "g");
    g.grad = 1.0;

    struct Stack stack;

    int initial_capacity = 100;
    init_stack(&stack, initial_capacity);

    dfs_to_stack(&g, &stack);

    backward_stack(&stack);

    print_stack(&stack);
    cleanup_stack(&stack);

    free_value(&c);
    free_value(&g);
}

void
test_3(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b)
{
    struct Value x1w1 = w_mul(&x1, &w1, "x1w1");
    struct Value x2w2 = w_mul(&x2, &w2, "x2w2");
    struct Value x1w1x2w2 = w_add(&x1w1, &x2w2, "x1*w1 + x2*w2");
    struct Value n = w_add(&x1w1x2w2, &b, "n");
    struct Value o = w_tanh(&n, "o");

    o.grad = 1.0;

    struct Stack stack;

    int initial_capacity = 100;
    init_stack(&stack, initial_capacity);

    dfs_to_stack(&o, &stack);

    backward_stack(&stack);

    print_stack(&stack);

    cleanup_stack(&stack);

    free_value(&x1w1);
    free_value(&x2w2);
    free_value(&x1w1x2w2);
    free_value(&n);
    free_value(&o);
}

void
test_4(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z)
{
    struct Value x1w1 = w_mul(&x1, &w1, "x1w1");
    struct Value x2w2 = w_mul(&x2, &w2, "x2w2");
    struct Value x1w1x2w2 = w_add(&x1w1, &x2w2, "x1*w1 + x2*w2");

    struct Value n = w_add(&x1w1x2w2, &b, "n");

    /* // Intermediate values. */
    struct Value x = w_mul(&n, &z, "x");

    /* /\* e = (2*n).exp() *\/ */
    struct Value e = w_exp(&x, "e");

    e.grad = 1.0;

    struct Stack stack;

    int initial_capacity = 100;
    init_stack(&stack, initial_capacity);

    dfs_to_stack(&e, &stack);

    backward_stack(&stack);

    print_stack(&stack);

    cleanup_stack(&stack);

    free_value(&x1w1);
    free_value(&x2w2);
    free_value(&x1w1x2w2);
    free_value(&n);
    free_value(&x);
    free_value(&e);
}

void
test_5(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z, struct Value io1)
{
    struct Value x1w1 = w_mul(&x1, &w1, "x1w1");
    struct Value x2w2 = w_mul(&x2, &w2, "x2w2");
    struct Value x1w1x2w2 = w_add(&x1w1, &x2w2, "x1*w1 + x2*w2");

    struct Value n = w_add(&x1w1x2w2, &b, "n");

    // Intermediate values.
    struct Value x = w_mul(&n, &z, "x");

    ///\* e = (2*n).exp() *\/ */
    struct Value e = w_exp(&x, "e");

    // Intermediate values.
    // struct Value io2 = create_value(1.0, "io2");
    struct Value io3 = w_add(&e, &io1, "io3");
    // struct Value io4 = w_add(&e, &io2, "io4");

    // o = (e - 1) / (e + 1)
    // struct Value o = w_div(&io3, &io4, "o");

    io3.grad = 1.0;

    struct Stack stack;

    int initial_capacity = 100;
    init_stack(&stack, initial_capacity);

    dfs_to_stack(&io3, &stack);

    backward_stack(&stack);

    print_stack(&stack);

    cleanup_stack(&stack);

    free_value(&x1w1);
    free_value(&x2w2);
    free_value(&x1w1x2w2);
    free_value(&n);
    free_value(&x);
    free_value(&e);
    free_value(&io3);
}

void
test_6(struct Neuron *n1, struct Neuron *n2, struct Neuron *n3, struct Value *inputs)
{
    forward_neuron(&n1, &inputs);
    /* forward_neuron(n2, inputs); */
    /* forward_neuron(n3, inputs); */
}

void
test_7()
{
    struct Layer *layer_test = create_layer(2, 3);

    struct Value in1 = create_value(2.0, "in1");
    struct Value in2 = create_value(3.0, "in2");
    struct Value inputs[] = {in1, in2};

    forward_layer(layer_test, inputs);

    free_layer(layer_test);
}

void
test_8()
{
    int n_layers = 5;
    struct MLP my_mlp = create_mlp(10, n_layers);

    struct Value in1 = create_value(2.0, "in1");
    struct Value in2 = create_value(3.0, "in2");
    struct Value inputs[] = {in1, in2};

    forward_mlp(&my_mlp, inputs);

    destroy_mlp(&my_mlp);
}
