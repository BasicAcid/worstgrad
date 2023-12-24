#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/* struct MLP */
/* *create_mlp(int nin, int n_out) */
/* { */
/*     size_t mlp_size = sizeof(struct MLP) + (long unsigned int)n_out * sizeof(struct Neuron); */
/*     struct MLP *mlp = malloc(mlp_size); */

/*     for(int i = 0; i < n_out; i++) */
/*     { */
/*     } */

/*     return mlp; */
/* } */


struct MLP
create_mlp(int nin, int numLayers)
{
    struct MLP mlp;
    mlp.nin = nin;

    mlp.nouts = (int *)malloc((long unsigned int)numLayers * sizeof(int));
    mlp.layers = (struct Layer *)malloc((long unsigned int)numLayers * sizeof(struct Layer));

    return mlp;
}

void
destroy_mlp(struct MLP *mlp)
{
    free(mlp->nouts);
    free(mlp->layers);
}
