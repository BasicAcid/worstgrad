#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include "main.h"

void
test_create_val()
{
    struct Value a = create_value(-2, "a");
    a.grad = 1.0;
    assert(a.data == -2);
    assert(strcmp(a.label, "a") == 0);
    assert(a.grad == 1.0);
}

void
test_add()
{
    struct Value a = create_value(-2, "a");
    struct Value b = create_value(3, "b");
    struct Value c = w_add(&a, &b, "c");
    assert(c.data == 1);
}

void
test_sub()
{
    struct Value a = create_value(-2, "a");
    struct Value b = create_value(3, "b");
    struct Value c = w_sub(&a, &b, "c");
    assert(c.data == -5);
}

void
test_mul()
{
    struct Value a = create_value(-2, "a");
    struct Value b = create_value(3, "b");
    struct Value c = w_mul(&a, &b, "c");
    assert(c.data == -6);
}

void
test_div()
{
    struct Value a = create_value(-4, "a");
    struct Value b = create_value(2, "b");
    struct Value c = w_div(&a, &b, "c");
    assert(c.data == -2);
}

void
test_tanh()
{
    struct Value a = create_value(2, "a");;
    struct Value b = w_tanh(&a, "b");
    assert(fabs(b.data - 0.964028) < 1e-6);
}

void
test_relu()
{
    struct Value a = create_value(2, "a");
    struct Value b = w_relu(&a, "b");

    struct Value c = create_value(-2, "c");
    struct Value d = w_relu(&c, "d");

    assert(b.data == 2);
    assert(d.data == 0);
}

void
test_exp()
{
    struct Value a = create_value(2, "a");
    struct Value b = create_value(-2, "b");

    struct Value c = w_exp(&a, "c");
    struct Value d = w_exp(&b, "d");

    assert(fabs(c.data - 7.389056) < 1e-6);
    assert(fabs(d.data - 0.135335) < 1e-6);
}

void
test_pow()
{
    struct Value a = create_value(2, "a");
    struct Value b = create_value(-2, "b");
    struct Value c = w_pow(&a, &b, "c");
    assert(fabs(c.data - 0.250000) < 1e-6);
}

void
test_add_backward()
{
    struct Value a = create_value(4, "a");
    struct Value b = create_value(-2, "b");
    struct Value c = w_add(&a, &b, "c");
    c.grad = 1.0;
    backward(&c);

    assert(a.grad == 1);
    assert(b.grad == 1);
}

void
test_sub_backward()
{
    struct Value a = create_value(4, "a");
    struct Value b = create_value(-2, "b");
    struct Value c = w_sub(&a, &b, "c");
    c.grad = 1.0;
    backward(&c);

    assert(a.grad == -1);
    assert(b.grad == -1);
}

void
test_mul_backward()
{
    struct Value a = create_value(4, "a");
    struct Value b = create_value(-2, "b");
    struct Value c = w_mul(&a, &b, "c");
    c.grad = 1.0;
    backward(&c);

    assert(a.grad == b.data);
    assert(b.grad == a.data);
}

void
test_div_backward()
{
    struct Value a = create_value(4, "a");
    struct Value b = create_value(-2, "b");
    struct Value c = w_div(&a, &b, "c");
    c.grad = 1.0;
    backward(&c);

    assert(a.grad == (1.0 / b.data));
    assert(b.grad == (-a.data / (b.data * b.data)));
}

void
test_tanh_backward()
{
    struct Value a = create_value(4, "a");
    struct Value b = w_tanh(&a, "b");
    b.grad = 1.0;
    backward(&b);

    assert(fabs(a.grad - 0.001341) < 1e-6);
}

void
test_exp_backward()
{
    struct Value a = create_value(-2, "a");
    struct Value b = w_exp(&a, "b");
    b.grad = 1.0;
    backward(&b);

    assert(fabs(a.grad - 0.135335) < 1e-6);
}

void
test_relu_backward()
{
    struct Value a = create_value(2, "a");
    struct Value b = w_relu(&a, "b");

    struct Value c = create_value(-2, "c");
    struct Value d = w_relu(&c, "d");

    b.grad = 1.0;
    d.grad = 1.0;

    backward(&b);
    backward(&d);

    assert(a.grad == 2);
    assert(c.grad == 0);
}

void
test_1()
{
    struct Value a = create_value(2, "a");
    struct Value b = create_value(-2, "b");
    struct Value c = w_sub(&a, &b, "c");
    struct Value d = w_tanh(&c, "d");

    d.grad = 1.0;

    size_t graph_size = 0;
    get_graph_size(&d, &graph_size);

    printf("%d\n", graph_size);

    /* struct Stack stack; */

    /* size_t initial_capacity = graph_size; */
    /* init_stack(&stack, initial_capacity); */

    /* dfs_to_stack(&d, &stack); */

    /* double h = 0.001; */

    /* gradient_descent(&stack, h, 100); */

    /* backward_stack(&stack); */

    /* //print_stack(&stack); */

    /* cleanup_stack(&stack); */
}
