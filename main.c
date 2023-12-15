#include <stdio.h>
#include <string.h>
#include "main.h"
#include </usr/include/graphviz/gvc.h>

int
main(void)
{
    /* Test template 1. ******************************************************/

    struct Value a = create_value(-2, "a");
    struct Value b = create_value(3, "b");
    struct Value d = w_mul(&a, &b, "d");
    struct Value e = w_add(&a, &b, "e");
    struct Value f = w_mul(&d, &e, "f");
    struct Value g = w_tanh(&f, "g");

    g.grad = 1.0;

    struct Stack stack;

    // Find a way to automate this.
    int initial_capacity = 100;
    init_stack(&stack, initial_capacity);

    dfs_to_stack(&g, &stack);

    double h = 0.001;

    grandent_descent(&stack, h, 200);

    // Print the content of the stack.
    for(int i = stack.top; i >= 0; i--)
    {
        print_node(stack.items[i]);
    }

    cleanup_stack(&stack);

    /* Test template 2. ******************************************************/

    /* struct Value x1 = create_value(2.0, "x1"); */
    /* struct Value x2 = create_value(0.0, "x2"); */
    /* struct Value w1 = create_value(-3.0, "w1"); */
    /* struct Value w2 = create_value(1.0, "w2"); */

    /* struct Value b = create_value(6.8813735870195432, "b"); */

    /* struct Value x1w1 = mul(&x1, &w1, "x1w1"); */
    /* struct Value x2w2 = mul(&x2, &w2, "x2w2"); */
    /* struct Value x1w1x2w2 = add(&x1w1, &x2w2, "x1*w1 + x2*w2"); */

    /* struct Value n = add(&x1w1x2w2, &b, "n"); */

    /* // Intermediate values. */
    /* struct Value z = create_value(2.0, "z"); */
    /* struct Value x = mul(&n, &z, "x"); */

    /* /\* e = (2*n).exp() *\/ */
    /* struct Value e = _exp(&x, "e"); */

    /* // Intermediate values. */
    /* struct Value io1 = create_value(1.0, "io1"); */
    /* struct Value io2 = create_value(1.0, "io2"); */
    /* struct Value io3 = sub(&e, &io1, "io3"); */
    /* struct Value io4 = add(&e, &io2, "io4"); */

    /* /\* o = (e - 1) / (e + 1) *\/ */
    /* struct Value o = _div(&io3, &io4, "o"); */

    /* o.grad = 1; */

    /* struct Stack stack; */
    /* stack.top = -1; */

    /* backward_dfs(&o, &stack); */

    /* dfs_topological(&o, &stack); */

    /* while (stack.top >= 0) { */
    /*     struct Value* node = pop(&stack); */
    /*     printf("Data: %f, Label: %s, Grad: %f\n", node->data, node->label, node->grad); */
    /* } */

    /* Neuron test template **************************************************/

    /* struct Neuron *neuneu = create_neuron(2); */
    /* struct Neuron *nana = create_neuron(2); */
    /* struct Neuron *noutnout = create_neuron(2); */

    /* struct Value in1 = create_value(2.0, "in1"); */
    /* struct Value in2 = create_value(3.0, "in2"); */
    /* struct Value in3 = create_value(5.0, "in2"); */
    /* struct Value inputs[] = {in1, in2, in3}; */

    /* init_neuron(neuneu, inputs); */
    /* init_neuron(nana, inputs); */
    /* init_neuron(noutnout, inputs); */

    /* free_neuron(neuneu); */
    /* free_neuron(nana); */
    /* free_neuron(noutnout); */

    //struct Layer *layer_test = create_layer(10, 10);

    //free_layer(layer_test);

    //free_neuron(&layer_test->neurons[0]);

    //init_layer(layer_test, inputs);

    //init_neuron(&layer_test->neurons[0], inputs);
    //init_neuron(&layer_test->neurons[1], inputs);
    //init_neuron(&layer_test->neurons[2], inputs);

    /* graphviz **************************************************************/

    /* Agraph_t *graph; */
    /* GVC_t *gvc; */

    /* gvc = gvContext(); */
    /* graph = agopen("my_graph", Agdirected, NULL); */

    /* Agnode_t *node1, *node2; */
    /* Agedge_t *edge; */

    /* // Add createflag argument to agnode calls */
    /* node1 = agnode(graph, "Node 1", 1); */
    /* node2 = agnode(graph, "Node 2", 1); */
    /* edge = agedge(graph, node1, node2, NULL, 1); */

    /* gvLayout(gvc, graph, "dot"); */
    /* gvRenderFilename(gvc, graph, "png", "output.png"); */

    /* gvFreeLayout(gvc, graph); */
    /* agclose(graph); */



    /* Agraph_t *graph; */
    /* GVC_t *gvc; */

    /* gvc = gvContext(); */
    /* graph = agopen("my_graph", Agdirected, NULL); */

    /* while (stack.top >= 0) { */
    /*     struct Value* node = pop(&stack); */
    /*     printf("Data: %f, Label: %s, Grad: %f\n", node->data, node->label, node->grad); */

    /* } */

    /* Agnode_t *node1, *node2; */
    /* //Agedge_t *edge; */

    /* // Add createflag argument to agnode calls */
    /* node1 = agnode(graph, "Node 1", 1); */
    /* node2 = agnode(graph, "Node 2", 1); */
    /* //edge = agedge(graph, node1, node2, NULL, 1); */

    /* gvLayout(gvc, graph, "dot"); */
    /* gvRenderFilename(gvc, graph, "png", "output.png"); */

    /* gvFreeLayout(gvc, graph); */
    /* agclose(graph); */




    return 0;
}
