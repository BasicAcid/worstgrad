#include <stdbool.h>
#include <stdio.h>

// TODO: This will create problems in the future.
enum { max_parents = 2 };

struct Arena
{
    size_t size;
    char* start;
    char* current;
};

struct Value
{
    struct Value *parents[max_parents];
    double data;
    double grad;
    /* char *label; */
    char label[20];
    char operator[5]; // TODO: bad...
    unsigned int visited : 1; // For topological sort.
};

struct Stack
{
    struct Value **items;
    int top;
    int capacity;
};

struct Neuron
{
    struct Value bias;
    struct Value output;
    int n_inputs;
    struct Value *weights;
};

struct Layer
{
    int nin;
    int nout;
    struct Neuron **neurons;
};

struct MLP
{
    int nin;
    int *nouts;
    struct Layer *layers;
};

struct Arena *create_arena(size_t size);
void free_arena(struct Arena* arena);

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
void init_stack(struct Stack *stack, int initial_capacity);
void cleanup_stack(struct Stack *stack);
void grandient_descent(struct Stack *stack, double h, int n);
void print_stack(struct Stack *stack);

void free_neuron(struct Neuron *neuron);
struct Neuron *create_neuron(int n_weights);
void forward_neuron(struct Neuron *neuron, struct Value *inputs[]);
void print_neuron(struct Neuron *n);

struct Layer *create_layer(int nin, int n_out);
void free_layer(struct Layer *layer);
void forward_layer(struct Layer *layer, struct Value *inputs[]);

struct MLP create_mlp(int nin, int n_layers);
void forward_mlp(struct MLP *mlp, struct Value inputs[]);
void destroy_mlp(struct MLP *mlp);

// Tests
void test_1(struct Value a, struct Value b);
void test_2(struct Value a, struct Value b);
void test_3(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b);
void test_4(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z);
void test_5(struct Value x1, struct Value x2, struct Value w1, struct Value w2, struct Value b, struct Value z, struct Value io1);
void test_6(struct Neuron *n1, struct Neuron *n2, struct Neuron *n3, struct Value *inputs[]);
void test_7(struct Value *inputs[]);
