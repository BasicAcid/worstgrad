#include <stdbool.h>
#include <stdio.h>

// TODO: This will create problems in the future.
enum { max_parents = 2 };

struct Value
{
    struct Value* parents[max_parents];
    double data;
    double grad;
    char label[20];
    char operator[5];
    unsigned int visited : 1; // For topological sort.
};

// Define operations enum
typedef enum {
    VALUE,
    ADD,
    SUB,
    MUL
} Operation;

struct Stack
{
    struct Value **items;
    int top;
    int capacity;
};

struct Value create_value(double data, const char *label);

void free_value(struct Value *val);

struct Value w_add(struct Value *v1, struct Value *v2, const char *label);
struct Value w_sub(struct Value *v1, struct Value *v2, const char *label);
struct Value w_mul(struct Value *v1, struct Value *v2, const char *label);
struct Value w_div(struct Value *v1, struct Value *v2, const char *label);
struct Value w_tanh(struct Value *v, const char *label);
struct Value w_relu(struct Value *v, const char *label);
struct Value w_exp(struct Value *v, const char *label);
struct Value w_pow(struct Value *v1, struct Value *v2, const char *label);

void get_parents(struct Value *v);
struct Value *get_parents2(struct Value *v);
void print_node(struct Value *v);

void backward(struct Value *result);
void backward_stack(struct Stack *stack);
void forward_stack(struct Stack *stack, double h);
void dfs_to_stack(struct Value *node, struct Stack *stack);
struct Value *pop(struct Stack *stack);
void push(struct Stack *stack, struct Value *new_value);
struct Value *peek(struct Stack *stack);
void init_stack(struct Stack *stack, size_t initial_capacity);
void cleanup_stack(struct Stack *stack);
void gradient_descent(struct Stack *stack, double h, int n);
void print_stack(struct Stack *stack);
size_t get_graph_size(struct Value *node, size_t *graph_size);

// Tests
void test_create_val();
void test_add();
void test_sub();
void test_mul();
void test_div();
void test_tanh();
void test_relu();
void test_exp();
void test_pow();

void test_add_backward();
void test_sub_backward();
void test_mul_backward();
void test_div_backward();
void test_tanh_backward();
void test_exp_backward();
void test_relu_backward();

void test_1();
void test_2(struct Value a, struct Value b);
void test_3(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b);
void test_4(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z);
void test_5(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z, struct Value io1);
