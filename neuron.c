#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

// Create a Neuron instance with a weights array of size 'n_weights'.
struct Neuron
*create_neuron(int n_weights)
{
    // Allocate memory for the entire structure, including the weights array.
    size_t neuron_size = sizeof(struct Neuron) + sizeof(struct Value) * (long unsigned int)n_weights;
    struct Neuron *neuron = malloc(neuron_size);

    if (neuron == NULL)
    {
        return NULL;
    }

    neuron->n_inputs = n_weights;

    // Set the pointer for the weights array.
    neuron->weights = (struct Value *)((char *)neuron + sizeof(struct Neuron));

    // Seed the random number generator with a combination of current time and a counter.
    // This is pretty bad, either replace with somtheing simpler, or something better.
    static unsigned int counter = 0;  // Static variable retains its value between calls
    srand48((long int)(time(NULL) + counter));

    for (int i = 0; i < n_weights; i++)
    {
        // Use drand48 for better randomness and a uniform distribution between [0, 1)
        neuron->weights[i].data = -1.0 + 2.0 * drand48();
    }

    // Random bias between -1 and 1.
    neuron->bias.data = -1.0 + 2.0 * drand48();

    neuron->n_inputs = n_weights;

    neuron->output.data = 0.0;

    // Increment the counter for the next function call.
    counter++;

    return neuron;
}


void
init_neuron(struct Neuron *neuron, struct Value inputs[])
{
    printf("Weights:\n");

    for(int i = 0; i < neuron->n_inputs; i++)
    {
        neuron->output.data = (neuron->weights[i].data * inputs[i].data) + neuron->bias.data;
    }

    neuron->output = w_tanh(&neuron->output, "output");
}

void
free_neuron(struct Neuron *neuron)
{
    free(neuron);
}

void
print_neuron(struct Neuron *n)
{
    printf("Bias: %lf\n", n->bias.data);

    printf("Output: %lf\n", n->output.data);

    for(int i = 0; i < n->n_inputs; i++)
    {
        printf("Weight %d: %lf\n", i, n->weights[i].data);
    }
}
