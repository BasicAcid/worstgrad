#include <stdbool.h>

enum { max_parents = 2 };

struct Value
{
    double data;
    double grad;
    char label[30];
    char operator[10];
    struct Value *parents[max_parents];
    void (*backward)(struct Value*);
    bool visited; // For topological sort.
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
    struct Neuron neurons[];
};

struct MLP
{
    int nin;
    int *nouts;
    struct Layer *layers;
};

struct Value create_value(double data, const char *label);

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
void push(struct Stack *stack, struct Value *newValue);
struct Value *peek(struct Stack *stack);
void init_stack(struct Stack *stack, int initial_capacity);
void cleanup_stack(struct Stack *stack);
void grandient_descent(struct Stack *stack, double h, int n);
void print_stack(struct Stack *stack);

void free_neuron(struct Neuron *neuron);
struct Neuron *create_neuron(int n_weights);
void forward_neuron(struct Neuron *neuron, struct Value inputs[]);
void print_neuron(struct Neuron *n);

struct Layer *create_layer(int nin, int n_neurons);
void free_layer(struct Layer *layer);
void forward_layer(struct Layer *layer, struct Value inputs[]);

struct MLP create_mlp(int nin, int numLayers);
void forward_mlp(struct MLP *mlp, struct Value inputs[]);
void destroy_mlp(struct MLP *mlp);
