#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"
#include <sys/time.h>

// Necessary to get a different value each time
// create_neuron is called.
long int global_seed = 0;

struct Neuron *create_neuron(int n_weights)
{
    size_t neuron_size = sizeof(struct Neuron) + sizeof(struct Value) * (long unsigned int)n_weights;

    struct Neuron *neuron = malloc(neuron_size);

    if(neuron == NULL)
    {
        fprintf(stderr, "Error (create_neuron): Unable to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    neuron->n_inputs = n_weights;

    // Set the pointer for the weights array.
    neuron->weights = (struct Value *)((char *)neuron + sizeof(struct Neuron));

    if (global_seed == 0)
    {
        // Initialize the seed only if it's not set.
        struct timeval currentTime;
        gettimeofday(&currentTime, NULL);
        global_seed = currentTime.tv_sec * 1000 + currentTime.tv_usec / 1000;
        srand48(global_seed);
    }

    for (int i = 0; i < n_weights; i++)
    {
        // Use drand48 for better randomness and a uniform distribution between [0, 1)
        neuron->weights[i].data = -1.0 + 2.0 * drand48();
    }

    // Random bias between -1 and 1.
    neuron->bias.data = -1.0 + 2.0 * drand48();

    neuron->n_inputs = n_weights;

    neuron->output.data = 0.0;

    return neuron;
}

void
forward_neuron(struct Neuron *neuron, struct Value *inputs[])
{
    for(int i = 0; i < neuron->n_inputs; i++)
    {
        //neuron->output.data += neuron->weights[i].data * inputs[i]->data;
        //neuron->output.data += inputs[i]->data;
        // TODO: Allocation bug
        // inputs[i]->data is not set correctly.
        /* printf("%f\n", inputs[i]->data); */
        /* printf("%d\n", i); */
    }

    neuron->output.data += neuron->bias.data;

    // Activation: uncomment tanh or relu:
    neuron->output = w_tanh(&neuron->output, "output");
    //neuron->output = w_relu(&neuron->output, "output");

    if (neuron->output.label != NULL)
    {
        free(neuron->output.label);
        neuron->output.label = NULL;
    }
}

void
free_neuron(struct Neuron *neuron)
{
    if(neuron != NULL)
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
