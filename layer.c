#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct Layer
*create_layer(int nin, int n_out)
{
   size_t layer_size = sizeof(struct Layer) + (long unsigned int)n_out * sizeof(struct Neuron);

   struct Layer *layer = malloc(layer_size);

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
    if(layer == NULL)
        return;

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
        print_neuron(&layer->neurons[i]);

        //free_neuron(&layer->neurons[i]);
    }

    //free(layer->neurons);

    free(layer);
}
