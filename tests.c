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

    struct Stack stack;

    size_t initial_capacity = graph_size;
    init_stack(&stack, initial_capacity);

    dfs_to_stack(&d, &stack);

    double h = 0.001;

    gradient_descent(&stack, h, 100);

    backward_stack(&stack);

    //print_stack(&stack);

    cleanup_stack(&stack);
}

void
test_node()
{
    Node *a = create_node("a", VALUE, 0, NULL);
    /* Node *b = create_node("b", VALUE, 0, NULL); */
    /* Node *c = create_node("c", SUB, 2, (Node*[]){a, b}); */
}

/* void */
/* test_2(struct Value a, struct Value b) */
/* { */
/*     struct Value c = w_mul(&a, &b, "c"); */
/*     struct Value g = w_tanh(&c, "g"); */
/*     g.grad = 1.0; */

/*     struct Stack stack; */

/*     int initial_capacity = 100; */
/*     init_stack(&stack, initial_capacity); */

/*     dfs_to_stack(&g, &stack); */

/*     backward_stack(&stack); */

/*     print_stack(&stack); */
/*     cleanup_stack(&stack); */

/*     free_value(&c); */
/*     free_value(&g); */
/* } */

/* void */
/* test_3(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b) */
/* { */
/*     struct Value x1w1 = w_mul(&x1, &w1, "x1w1"); */
/*     struct Value x2w2 = w_mul(&x2, &w2, "x2w2"); */
/*     struct Value x1w1x2w2 = w_add(&x1w1, &x2w2, "x1*w1 + x2*w2"); */
/*     struct Value n = w_add(&x1w1x2w2, &b, "n"); */
/*     struct Value o = w_tanh(&n, "o"); */

/*     o.grad = 1.0; */

/*     struct Stack stack; */

/*     int initial_capacity = 100; */
/*     init_stack(&stack, initial_capacity); */

/*     dfs_to_stack(&o, &stack); */

/*     backward_stack(&stack); */

/*     print_stack(&stack); */

/*     cleanup_stack(&stack); */

/*     free_value(&x1w1); */
/*     free_value(&x2w2); */
/*     free_value(&x1w1x2w2); */
/*     free_value(&n); */
/*     free_value(&o); */
/* } */

/* void */
/* test_4(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z) */
/* { */
/*     struct Value x1w1 = w_mul(&x1, &w1, "x1w1"); */
/*     struct Value x2w2 = w_mul(&x2, &w2, "x2w2"); */
/*     struct Value x1w1x2w2 = w_add(&x1w1, &x2w2, "x1*w1 + x2*w2"); */

/*     struct Value n = w_add(&x1w1x2w2, &b, "n"); */

/*     /\* // Intermediate values. *\/ */
/*     struct Value x = w_mul(&n, &z, "x"); */

/*     /\* /\\* e = (2*n).exp() *\\/ *\/ */
/*     struct Value e = w_exp(&x, "e"); */

/*     e.grad = 1.0; */

/*     struct Stack stack; */

/*     int initial_capacity = 100; */
/*     init_stack(&stack, initial_capacity); */

/*     dfs_to_stack(&e, &stack); */

/*     backward_stack(&stack); */

/*     print_stack(&stack); */

/*     cleanup_stack(&stack); */

/*     free_value(&x1w1); */
/*     free_value(&x2w2); */
/*     free_value(&x1w1x2w2); */
/*     free_value(&n); */
/*     free_value(&x); */
/*     free_value(&e); */
/* } */

/* void */
/* test_5(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z, struct Value io1) */
/* { */
/*     struct Value x1w1 = w_mul(&x1, &w1, "x1w1"); */
/*     struct Value x2w2 = w_mul(&x2, &w2, "x2w2"); */
/*     struct Value x1w1x2w2 = w_add(&x1w1, &x2w2, "x1*w1 + x2*w2"); */

/*     struct Value n = w_add(&x1w1x2w2, &b, "n"); */

/*     // Intermediate values. */
/*     struct Value x = w_mul(&n, &z, "x"); */

/*     ///\\* e = (2*n).exp() *\\/ *\/ */
/*     struct Value e = w_exp(&x, "e"); */

/*     // Intermediate values. */
/*     // struct Value io2 = create_value(1.0, "io2"); */
/*     struct Value io3 = w_add(&e, &io1, "io3"); */
/*     // struct Value io4 = w_add(&e, &io2, "io4"); */

/*     // o = (e - 1) / (e + 1) */
/*     // struct Value o = w_div(&io3, &io4, "o"); */

/*     io3.grad = 1.0; */

/*     struct Stack stack; */

/*     int initial_capacity = 100; */
/*     init_stack(&stack, initial_capacity); */

/*     dfs_to_stack(&io3, &stack); */

/*     backward_stack(&stack); */

/*     print_stack(&stack); */

/*     cleanup_stack(&stack); */

/*     free_value(&x1w1); */
/*     free_value(&x2w2); */
/*     free_value(&x1w1x2w2); */
/*     free_value(&n); */
/*     free_value(&x); */
/*     free_value(&e); */
/*     free_value(&io3); */
/* } */

/* void */
/* test_6(struct Neuron *n1, struct Neuron *n2, struct Neuron *n3, struct Value *inputs[]) */
/* { */
/*     //printf("Number of inputs: %d\n", n1->n_inputs); */
/*     forward_neuron(n1, inputs); */
/*     forward_neuron(n2, inputs); */
/*     forward_neuron(n3, inputs); */
/* } */

/* void */
/* test_7(struct Value *inputs[]) */
/* { */
/*     struct Layer *layer_test = create_layer(24, 39); */

/*     forward_layer(layer_test, inputs); */

/*     free_layer(layer_test); */
/* } */

/* void */
/* test_8() */
/* { */
/*     int n_layers = 5; */
/*     struct MLP my_mlp = create_mlp(10, n_layers); */

/*     struct Value in1 = create_value(2.0, "in1"); */
/*     struct Value in2 = create_value(3.0, "in2"); */
/*     struct Value inputs[] = {in1, in2}; */

/*     forward_mlp(&my_mlp, inputs); */

/*     destroy_mlp(&my_mlp); */
/* } */
