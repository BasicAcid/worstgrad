#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct Layer *create_layer(int nin, int n_out)
{
    struct Layer *layer = malloc(sizeof(struct Layer));

    if(layer == NULL)
    {
        fprintf(stderr, "Error (create_layer): Unable to allocate memory for layer.\n");
        exit(EXIT_FAILURE);
    }

    layer->neurons = malloc((long unsigned int)n_out * sizeof(struct Neuron));

    if(layer->neurons == NULL)
    {
        fprintf(stderr, "Error (create_layer): Unable to allocate memory for neurons.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < n_out; i++)
    {
        layer->neurons[i] = *create_neuron(nin);
    }

    layer->nin = nin;
    layer->nout = n_out;

    return layer;
}

void
forward_layer(struct Layer *layer, struct Value inputs[])
{
    if (layer == NULL)
    {
        fprintf(stderr, "Error (forward_layer): Unable to allocate memory.\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < layer->nout; i++)
    {
        forward_neuron(&layer->neurons[i], inputs);
    }
}

void
free_layer(struct Layer *layer)
{
    if(layer == NULL)
        return;

    for(int i = 0; i < layer->nout; i++)
    {
        //print_neuron(&layer->neurons[i]);

        //free_neuron(&layer->neurons[i]);
    }

    free(layer->neurons);

    free(layer);
}
