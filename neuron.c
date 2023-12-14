#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

// Create a Neuron instance with a weights array of size 'num_weights'
struct Neuron *create_neuron(int n_weights)
{
    // Allocate memory for the entire structure, including the weights array.
    size_t neuron_size = sizeof(struct Neuron) + sizeof(struct Value) * (long unsigned int)n_weights;
    struct Neuron *neuron = malloc(neuron_size);

    if (neuron == NULL)
    {
        return NULL;
    }

    neuron->n_inputs = n_weights;

    // Set the pointer for the weights array
    neuron->weights = (struct Value *)((char *)neuron + sizeof(struct Neuron));

    // Seed the random number generator with a combination of current time and a counter
    static unsigned int counter = 0;  // Static variable retains its value between calls
    srand48((long int)(time(NULL) + counter));

    for (int i = 0; i < n_weights; i++)
    {
        // Use drand48 for better randomness and a uniform distribution between [0, 1)
        neuron->weights[i].data = -1.0 + 2.0 * drand48();
    }

    // Random bias between -1 and 1
    neuron->bias.data = -1.0 + 2.0 * drand48();

    neuron->n_inputs = n_weights;

    neuron->output.data = 0.0;

    // Increment the counter for the next function call
    counter++;

    return neuron;
}

/* // (number of inputs per neuron, number of neurons) */
/* struct Layer *create_layer(int nin, int n_neurons) */
/* { */
/*     // Calculate the total size of the structure, including the flexible array. */
/*     struct Layer *layer = malloc(sizeof(struct Layer)); */
/*     if (layer == NULL) { */
/*         // Handle allocation failure */
/*         return NULL; */
/*     } */

/*     layer->nin = nin; */
/*     layer->nout = n_neurons; */

/*     // Allocate memory for the neurons array. */
/*     layer->neurons = malloc(n_neurons * sizeof(struct Neuron)); */
/*     if (layer->neurons == NULL) { */
/*         // Handle allocation failure */
/*         free(layer); */
/*         return NULL; */
/*     } */

/*     for (int i = 0; i < n_neurons; i++) */
/*     { */
/*         struct Neuron *new_neuron = create_neuron(nin); */
/*         if (new_neuron == NULL) { */
/*             // Handle create_neuron failure */
/*             free(layer->neurons); */
/*             free(layer); */
/*             return NULL; */
/*         } */
/*         layer->neurons[i] = *new_neuron; */
/*     } */

/*     return layer; */
/* } */

struct Layer *create_layer(int nin, int n_neurons)
{
    size_t layer_size = sizeof(struct Layer) + (long unsigned int)n_neurons * sizeof(struct Neuron);
    struct Layer *layer = malloc(layer_size);

    for (int i = 0; i < n_neurons; i++)
    {
        layer->neurons[i].weights = malloc((long unsigned int)layer->neurons[i].n_inputs * sizeof(struct Value));
        // Additional initialization for neurons
        // ...
    }

    layer->nin = nin;
    layer->nout = n_neurons;

    return layer;
}


void free_layer(struct Layer *layer)
{
    if (layer == NULL)
    {
        return; // Avoid dereferencing a null pointer
    }

    // Free each individual neuron in the layer.
    for (int i = 0; i < layer->nout; i++)
    {
        free_neuron(&layer->neurons[i]);
    }

    // Free the neurons array.
    free(layer->neurons);

    // Free the layer structure.
    free(layer);
}


void init_neuron(struct Neuron *neuron, struct Value inputs[])
{
    printf("Weights:\n");

    for(int i = 0; i < neuron->n_inputs; i++)
    {
        printf("%f\n", neuron->weights[i].data);
        neuron->output.data = (neuron->weights[i].data * inputs[i].data) + neuron->bias.data;
    }

    neuron->output = w_tanh(&neuron->output, "output");

    printf("Bias: %f\n", neuron->bias.data);
    printf("Output: %f\n", neuron->output.data);
}

void init_layer(struct Layer *layer, struct Value inputs[])
{
    for(int i = 0; i < layer->nin; i++)
    {
        init_neuron(&layer->neurons[i], inputs);

        //printf("neuneu: %f\n" , layer->neurons[i].weights[0].data);
    }
}

void free_neuron(struct Neuron *neuron)
{
    // Free the memory allocated for the weights array
    //free(neuron->weights);

    // Free the memory allocated for the structure
    free(neuron);
}
