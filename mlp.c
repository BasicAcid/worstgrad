#include <stdio.h>
#include <stdlib.h>
#include "main.h"

struct MLP
create_mlp(int nin, int n_layers)
{
    struct MLP mlp;
    mlp.nin = nin;

    size_t nout_size = (long unsigned int)n_layers * sizeof(int);
    size_t layer_size = (long unsigned int)n_layers * sizeof(struct Layer);

    mlp.nouts = (int *)malloc(nout_size);
    mlp.layers = (struct Layer *)malloc(layer_size);

    return mlp;
}

void
destroy_mlp(struct MLP *mlp)
{
    free(mlp->nouts);
    free(mlp->layers);
}
