#include <stdio.h>
#include <stdlib.h>
#include "main.h"


struct Layer
*create_layer(int nin, int n_out)
{
    size_t layer_size = sizeof(struct Layer) + (long unsigned int)n_out * sizeof(struct Neuron);
    struct Layer *layer = malloc(layer_size);

    //layer->neurons = calloc((size_t)layer->nout, sizeof(struct Neuron));


    for (int i = 0; i < n_out; i++)
    {
        /* size_t weights = malloc((long unsigned int)layer->neurons[i].n_inputs * sizeof(struct Value)); */
        /* layer->neurons[i].weights = weights; */

        //init_neuron(create_neuron(n_out), nin);

        layer->neurons[i] = *create_neuron(nin);

    }

    layer->nin = nin;
    layer->nout = n_out;

    return layer;
}



void
free_layer(struct Layer *layer)
{
    if(layer == NULL)
    {
        return;
    }

    for(int i = 0; i < layer->nout; i++)
    {
        print_neuron(&layer->neurons[i]);

        //free_neuron(&layer->neurons[i]);
    }

    //free(layer->neurons);

    free(layer);
}
