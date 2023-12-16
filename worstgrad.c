#include "main.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

struct Value
create_value(double data, const char *label)
{
    struct Value val;
    val.data = data;
    //val.grad = 1.0; // Gradient of a value with respect to itself is 1 ?
    // Answer: you fool, was causing a problem when called trough backward.
    // The right value is 0.
    val.grad = 0.0;
    snprintf(val.label, sizeof(val.label), "%s", label);  // Copy the label string.

    // Setting the operator to something is necessary for get_parents() .
    snprintf(val.operator, sizeof(val.operator), "root");

    // Magic number!
    for(int i = 0; i < 2; i++)
    {
        val.parents[i] = NULL;
    }

    val.backward = NULL;
    val.visited = false;
    return val;
}

void
set_parent(struct Value* result, int index, struct Value* parent)
{
    // Magic number!
    if(index >= 0 && index < 2)
    {
        result->parents[index] = parent;
    }
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
    // Which is better?
    // struct Value result = create_value(v1->data / v2->data, label);

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
    {
        result = create_value(0, label);
    }
    else
    {
        result = create_value(v->data, label);
    }
    result.grad = 0.0;
    snprintf(result.operator, sizeof(result.operator), "relu");
    set_parent(&result, 0, v);
    return result;
}

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
    //print_node(result);
    if(result->parents[0] != NULL)
    {
        result->parents[0]->grad += result->grad;
    }
    if(result->parents[1] != NULL)
    {
        result->parents[1]->grad += result->grad;
    }
}

void
sub_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
    {
        result->parents[0]->grad = 1.0 * result->grad;
    }
    if(result->parents[1] != NULL)
    {
        result->parents[1]->grad = 1.0 * result->grad;
    }
}

void
mul_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
    {
        //printf("%lf\n", result->parents[0]->grad);
        result->parents[0]->grad += result->parents[1]->data * result->grad;
    }
    if(result->parents[1] != NULL)
    {
        result->parents[1]->grad += result->parents[0]->data * result-> grad;
    }
}

void
div_backward(struct Value *result)
{
    if(result->parents[0] != NULL)
    {
        result->parents[0]->grad = 1 / result->parents[1]->data;
    }
    if(result->parents[1] != NULL)
    {
        result->parents[1]->grad = result->parents[0]->data / pow(result->parents[1]->data, 2);
    }
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
    {
        result->parents[0]->grad = result->grad * result->data;
    }
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
    {
        result->parents[0]->grad = result->data * result->grad;
    }
    else
    {
        result->parents[0]->grad = result->grad;
    }
}

void
backward(struct Value *result)
{
    if(strcmp(result->operator, "+") == 0)
    {
        add_backward(result);
    }
    else if(strcmp(result->operator, "-") == 0)
    {
        sub_backward(result);
    }
    else if(strcmp(result->operator, "*") == 0)
    {
        mul_backward(result);
    }
    else if(strcmp(result->operator, "/") == 0)
    {
        div_backward(result);
    }
    else if(strcmp(result->operator, "tanh") == 0)
    {
        tanh_backward(result);
    }
    else if(strcmp(result->operator, "exp") == 0)
    {
        exp_backward(result);
    }
    else if(strcmp(result->operator, "pow") == 0)
    {
        pow_backward(result);
    }
    else if(strcmp(result->operator, "relu") == 0)
    {
        relu_backward(result);
    }
}

void
get_parents(struct Value *v)
{
    if(strcmp("+", v->operator) == 0)
    {
        for(int i = 0; i < 2; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else if(strcmp("-", v->operator) == 0)
    {
        for(int i = 0; i < 2; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else if(strcmp("*", v->operator) == 0)
    {
        for(int i = 0; i < 2; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else if(strcmp("/", v->operator) == 0)
    {
        for(int i = 0; i < 2; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else if(strcmp("tanh", v->operator) == 0)
    {
        for(int i = 0; i < 1; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else if(strcmp("relu", v->operator) == 0)
    {
        for(int i = 0; i < 1; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else if(strcmp("exp", v->operator) == 0)
    {
        for(int i = 0; i < 1; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else if(strcmp("pow", v->operator) == 0)
    {
        for(int i = 0; i < 2; i++)
        {
            printf("Parent data: %lf\n", v->parents[i]->data);
        }
    }
    else
    {
        printf("Root node.");
    }
}

// Any use?
struct Value
*get_parents2(struct Value *v)
{
    struct Value *list;

    if(strcmp("+", v->operator) == 0)
    {
        list = (struct Value*)malloc(2 * sizeof(struct Value));

        for(int i = 0; i < 2; i++)
        {
            list[i] = *v->parents[i];
        }
    }

    else if(strcmp("-", v->operator) == 0)
    {
        list = (struct Value*)malloc(2 * sizeof(struct Value));

        for(int i = 0; i < 2; i++)
        {
            list[i] = *v->parents[i];
        }
    }
    else if(strcmp("*", v->operator) == 0)
    {
        list = (struct Value*)malloc(2 * sizeof(struct Value));

        for(int i = 0; i < 2; i++)
        {
            list[i] = *v->parents[i];
        }
    }
    else if(strcmp("/", v->operator) == 0)
    {
        list = (struct Value*)malloc(2 * sizeof(struct Value));

        for(int i = 0; i < 2; i++)
        {
            list[i] = *v->parents[i];
        }
    }
    else if(strcmp("tanh", v->operator) == 0)
    {
        list = (struct Value*)malloc(sizeof(struct Value));

        for(int i = 0; i < 1; i++)
        {
            list[i] = *v->parents[i];
        }
    }
    else if(strcmp("relu", v->operator) == 0)
    {
        list = (struct Value*)malloc(sizeof(struct Value));

        for(int i = 0; i < 1; i++)
        {
            list[i] = *v->parents[i];
        }
    }
    else if(strcmp("exp", v->operator) == 0)
    {
        list = (struct Value*)malloc(sizeof(struct Value));

        for(int i = 0; i < 1; i++)
        {
            list[i] = *v->parents[i];
        }
    }
    else if(strcmp("pow", v->operator) == 0)
    {
        list = (struct Value*)malloc(2 * sizeof(struct Value));

        for(int i = 0; i < 2; i++)
        {
            list[i] = *v->parents[i];
        }
    }
    else
    {
        /* list = (struct Value*)malloc(sizeof(struct Value)); */

        /* list = v; */
        return NULL;
    }
    return list;
}

void
print_node(struct Value *v)
{
    printf("Data: %f, Label: %s, Grad: %f, Op: %s, Vis: %d\n", v->data, v->label, v->grad, v->operator, v->visited);
}

void
print_graph(struct Value *head)
{
    struct Value *current = head;

    while(current != NULL)
    {
        printf("%lf -> ", current->data);
        current = current->parents[1];
    }
    printf("NULL\n");
}

void
init_stack(struct Stack *stack, int initial_capacity)
{
    stack->items = (struct Value **)malloc(
        (long unsigned int)initial_capacity * sizeof(struct Value *));
    stack->top = -1;
    stack->capacity = initial_capacity;
}

void
push(struct Stack *stack, struct Value *newValue)
{
    if(stack->top == stack->capacity - 1)
    {
        stack->capacity = stack->capacity * 2; // Growth (too much?)
        stack->items = (struct Value **)realloc(stack->items, (long unsigned int)stack->capacity * sizeof(struct Value *));
    }

    stack->top++;
    stack->items[stack->top] = newValue;
}

struct Value
*pop(struct Stack *stack)
{
    if(stack->top == -1)
    {
        return NULL;
    }

    struct Value *popped = stack->items[stack->top];
    stack->top--;

    return popped;
}

struct Value
*peek(struct Stack *stack)
{
    if(stack->top == -1)
    {
        return NULL;
    }

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

    for(int i = 0; i < 2; i++)
    {
        if(node->parents[i] != NULL && !node->parents[i]->visited)
        {
            dfs_to_stack(node->parents[i], stack);
        }
   }
    push(stack, node);
}

void
backward_stack(struct Stack *stack)
{
    for(int i = stack->top; i >= 0; i--)
    {
        struct Value *node = stack->items[i];
        backward(node);
    }
}

void
forward_stack(struct Stack *stack, double h)
{
    for(int i = 0; i <= stack->top; i++)
    {
        struct Value *node = stack->items[i];
        node->data += node->grad * h;
    }
}

void
grandient_descent(struct Stack *stack, double h, int n)
{
    for (int i = 0; i < n; ++i)
    {
        backward_stack(stack);
        forward_stack(stack, h);
    }
}

void
print_stack(struct Stack *stack)
{
    for(int i = stack->top; i >= 0; i--)
    {
        print_node(stack->items[i]);
    }
}
