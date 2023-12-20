#include <stdio.h>
#include <stdlib.h>
#include "main.h"

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

struct Layer *create_layer(int nin, int n_out)
{
    size_t layer_size = sizeof(struct Layer) + (long unsigned int)n_out * sizeof(struct Neuron);
    struct Layer *layer = malloc(layer_size);

    /* for (int i = 0; i < n_out; i++) */
    /* { */
    /*     /\* size_t weights = malloc((long unsigned int)layer->neurons[i].n_inputs * sizeof(struct Value)); *\/ */
    /*     /\* layer->neurons[i].weights = weights; *\/ */

    /*     //init_neuron(create_neuron(n_out), nin); */

    /* } */

    layer->nin = nin;
    layer->nout = n_out;

    return layer;
}


void free_layer(struct Layer *layer)
{
    if(layer == NULL)
    {
        return;
    }

    /* for(int i = 0; i < layer->nout; i++) */
    /* { */
    /*     printf("%lf\n" , &layer->neurons[i].output.data); */

    /*     //free_neuron(&layer->neurons[i]); */
    /* } */

    //free(layer->neurons);

    free(layer);
}

/* void init_layer(struct Layer *layer, struct Value inputs[]) */
/* { */
/*     for(int i = 0; i < layer->nin; i++) */
/*     { */
/*         init_neuron(&layer->neurons[i], inputs); */

/*         //printf("neuneu: %f\n" , layer->neurons[i].weights[0].data); */
/*     } */
/* } */
