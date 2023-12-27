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

void forward_mlp(struct MLP *mlp, struct Value inputs[])
{
    if(mlp == NULL)
        return;

    // From cppcheck:
    // mlp.c:25:13: warning: Using 'sizeof' on array given as function argument returns size of a pointer. [sizeofwithsilentarraypointer]
    // int n = sizeof(inputs)/sizeof(inputs[0]);

    //printf("%d\n", n);
    //printf("%lf\n", inputs[1].data);

    /* for(int i = 0; i < n; i++) */
    /* { */
    /*     //create_layer(); */
    /* } */
}

void
destroy_mlp(struct MLP *mlp)
{
    free(mlp->nouts);
    free(mlp->layers);
}
