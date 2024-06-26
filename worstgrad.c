#include "main.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

/* Node */
/* *create_node(char name[20], Operation op, size_t num_inputs, Node **inputs) */
/* { */
/*     Node *node = malloc(sizeof(Node)); */
/*     strncpy(node->name, name, 20 - 1); */
/*     node->name[20 - 1] = '\0'; // Ensure null termination */
/*     node->op = op; */
/*     node->inputs = inputs; */
/*     node->num_inputs = num_inputs; */
/*     node->grad = 0.0; */
/*     return node; */
/* } */

/* void */
/* forward_propagation(Node *node) */
/* { */
/*     switch (node->op) { */
/*         case VALUE: */
/*             break; */
/*         case ADD: */
/*             node->value = node->inputs[0]->value + node->inputs[1]->value; */
/*             break; */
/*         case SUB: */
/*             node->value = node->inputs[0]->value - node->inputs[1]->value; */
/*             break; */
/*         case MUL: */
/*             node->value = node->inputs[0]->value * node->inputs[1]->value; */
/*             break; */
/*     } */
/* } */

struct Value
create_value(double data, const char *label)
{
    struct Value val;

    val.data = data;
    val.grad = 0.0;

    strcpy(val.label, label);

    // Setting the operator to something is necessary for get_parents().
    snprintf(val.operator, sizeof(val.operator), "root");

    // Set the two parents to null (binop).
    for(int i = 0; i < 2; i++)
        val.parents[i] = NULL;

    val.visited = false;

    return val;
}

void
set_parent(struct Value* result, int index, struct Value *parent)
{
    // Between one (unary op like tanh) or two parents.
    if(index >= 0 && index < 2)
        result->parents[index] = parent;
}

struct Value
w_add(struct Value *v1, struct Value *v2, const char *label)
{
    struct Value result = create_value(v1->data + v2->data, label);
    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "+");
    set_parent(&result, 0, v1);
    set_parent(&result, 1, v2);
    return result;
}

struct Value
w_sub(struct Value *v1, struct Value *v2, const char *label)
{
    struct Value result = create_value(v1->data - v2->data, label);
    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "-");
    set_parent(&result, 0, v1);
    set_parent(&result, 1, v2);
    return result;
}

struct Value
w_mul(struct Value *v1, struct Value *v2, const char *label)
{
    struct Value result = create_value(v1->data * v2->data, label);
    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "*");
    set_parent(&result, 0, v1);
    set_parent(&result, 1, v2);
    return result;
}

struct Value
w_div(struct Value *v1, struct Value *v2, const char *label)
{
    struct Value ir1 = create_value(-1, "ir1");
    struct Value ir2 = w_pow(v2, &ir1, "ir2");
    struct Value result = create_value(v1->data * ir2.data, label);

    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "/");
    set_parent(&result, 0, v1);
    set_parent(&result, 1, v2);
    return result;
}

struct Value
w_tanh(struct Value *v, const char *label)
{
    struct Value result = create_value((expm1(2 * v->data)) / (exp(2 * v->data) + 1), label);
    snprintf(result.operator, sizeof(result.operator), "tanh");
    set_parent(&result, 0, v);
    return result;
}

struct Value
w_relu(struct Value *v, const char *label)
{
    struct Value result;

    if(v->data < 0)
        result = create_value(0, label);
    else
        result = create_value(v->data, label);

    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "relu");
    set_parent(&result, 0, v);
    return result;
}

/* // Set to a proper return type after implementation. */
/* //struct Value */
/* void */
/* softmax(struct Value *v, int arr_size) */
/* { */

/* } */

struct Value
w_exp(struct Value *v, const char *label)
{
    struct Value result = create_value((exp(v->data)), label);
    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "exp");
    set_parent(&result, 0, v);
    return result;
}

struct Value
w_pow(struct Value *v1, struct Value *v2, const char *label)
{
    // Conversion from double to float in powf, is it bad?
    struct Value result = create_value((powf((float)v1->data, (float)v2->data)), label);
    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "pow");
    set_parent(&result, 0, v1);
    set_parent(&result, 1, v2);
    return result;
}

void
add_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
        result->parents[0]->grad = result->grad;

    if(result->parents[1] != NULL)
        result->parents[1]->grad = result->grad;
}

void
sub_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
        result->parents[0]->grad -= result->grad;

    if(result->parents[1] != NULL)
        result->parents[1]->grad -= result->grad;
}

void
mul_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
        //printf("%lf\n", result->parents[0]->grad);
        result->parents[0]->grad += result->parents[1]->data * result->grad;

    if(result->parents[1] != NULL)
        result->parents[1]->grad += result->parents[0]->data * result-> grad;
}

void
div_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
        result->parents[0]->grad = 1 / result->parents[1]->data;

    if(result->parents[1] != NULL)
        result->parents[1]->grad -= result->parents[0]->data / pow(result->parents[1]->data, 2);
}

void
tanh_backward(struct Value *result)
{
    result->parents[0]->grad = (1 - pow(result->data, 2)) * result->grad;
}

void
exp_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
        result->parents[0]->grad = result->grad * result->data;
}

void
pow_backward(struct Value *result)
{
    // self.grad += other * self.data ** (other - 1) * out.grad
    result->parents[0]->grad += result->parents[1]->data * pow(result->parents[0]->data, (result->parents[1]->data - 1))  * result->grad;
}

void
relu_backward(struct Value *result)
{
    if(result->data > 0)
        result->parents[0]->grad = result->data * result->grad;
}

void
backward(struct Value *result)
{
    if(strcmp(result->operator, "+") == 0)
        add_backward(result);
    else if(strcmp(result->operator, "-") == 0)
        sub_backward(result);
    else if(strcmp(result->operator, "*") == 0)
        mul_backward(result);
    else if(strcmp(result->operator, "/") == 0)
        div_backward(result);
    else if(strcmp(result->operator, "tanh") == 0)
        tanh_backward(result);
    else if(strcmp(result->operator, "exp") == 0)
        exp_backward(result);
    else if(strcmp(result->operator, "pow") == 0)
        pow_backward(result);
    else if(strcmp(result->operator, "relu") == 0)
        relu_backward(result);
}

void
get_parents(struct Value *v) {
    int numParents = 0;

    if(strcmp("+", v->operator) == 0 ||
       strcmp("-", v->operator) == 0 ||
       strcmp("*", v->operator) == 0 ||
       strcmp("/", v->operator) == 0 ||
       strcmp("pow", v->operator) == 0)
    {
        numParents = 2;
    }
    else if(strcmp("tanh", v->operator) == 0 ||
            strcmp("relu", v->operator) == 0 ||
            strcmp("exp", v->operator) == 0)
    {
        numParents = 1;
    }

    if(numParents > 0)
    {
        for(int i = 0; i < numParents; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else
    {
        printf("Root node.\n");
    }
}

void
print_node(struct Value *v) {
    printf("Data: %f, Label: %s, Grad: %f, Op: %s, Vis: %u\n", v->data, v->label, v->grad, v->operator, v->visited);
}

size_t
get_graph_size(struct Value *node, size_t *graph_size)
{
    node->visited = true;

    for (int i = 0; i < 2; i++) {
        if (node->parents[i] != NULL && !node->parents[i]->visited) {
            get_graph_size(node->parents[i], graph_size);
        }
    }

    //(*graph_size)++;

    return *graph_size++;
}

void
init_stack(struct Stack* stack, size_t initial_capacity)
{
    size_t items_size = initial_capacity * sizeof(struct Value*);
    stack->items = malloc(items_size);
    stack->top = 0;
    stack->capacity = initial_capacity;
}

void
push(struct Stack *stack, struct Value *new_value)
{
    if (stack->top == stack->capacity) // Remove -1 from the comparison
    {
        stack->capacity *= 2;
        size_t items_size = stack->capacity * sizeof(struct Value *);
        stack->items = realloc(stack->items, items_size);
    }

    stack->items[stack->top] = new_value;
    stack->top++;
}

struct Value
*pop(struct Stack *stack)
{
    if(stack->top == 0)
        return NULL;

    struct Value *popped = stack->items[stack->top];
    stack->top--;

    return popped;
}

struct Value
*peek(struct Stack *stack)
{
    if(stack->top == 0)
        return NULL;

    struct Value *peeked = stack->items[stack->top];
    return peeked;
}

void
cleanup_stack(struct Stack *stack)
{
    free(stack->items);
}

// DFS over tree and push to stack in order.
void
dfs_to_stack(struct Value *node, struct Stack *stack)
{
    node->visited = true;

    for (int i = 0; i < 2; i++) {
        if (node->parents[i] != NULL && !node->parents[i]->visited) {
            dfs_to_stack(node->parents[i], stack);
        }
    }
    push(stack, node);
}

void
backward_stack(struct Stack *stack)
{
    for (size_t i = stack->top; i > 0; i--) {
        struct Value *node = stack->items[i];
        backward(node);
    }
}

void
forward_stack(struct Stack *stack, double h)
{
    for (size_t i = 0; i <= stack->top; i++) {
        struct Value *node = stack->items[i];
        node->data += node->grad * h;
    }
}

void
gradient_descent(struct Stack *stack, double h, size_t n)
{
    for (size_t i = 0; i < n; ++i) {
        backward_stack(stack);
        forward_stack(stack, h);
    }
}

void
print_stack(struct Stack *stack)
{
    for (size_t i = stack->top; i > 0; i--) {
        print_node(stack->items[i]);
    }
}
