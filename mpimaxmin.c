#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>
float *create_rand_nums(int num_elements)
{
    float *rand_nums = (float *)malloc(sizeof(float) * num_elements);
    assert(rand_nums != NULL);
    int i;
    for (i = 0; i < num_elements; i++)
    {
        rand_nums[i] = (rand() / (float)RAND_MAX);
    }

    return rand_nums;
}
int main(int argc, char **argv)
{
    if (argc != 2)
    {
     fprintf(stderr,"Usage: avg 
num_elments_per_proc\n");
     exit(1);
    }
    int num_elements_per_proc = atoi(argv[1]);

    MPI_Init(NULL, NULL);
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    srand(time(NULL) * world_rank);
    float *rand_nums = NULL;
    rand_nums = create_rand_nums(num_elements_per_proc);
    float max = 0;
    int k;
    for (k = 0; k < num_elements_per_proc; k++)
    {
        if (rand_nums[k] > max)
        {
            max = rand_nums[k];
        }
    }
    float global_max;
    MPI_Reduce(&max, &global_max, 1, MPI_FLOAT, MPI_MAX, 0,
               MPI_COMM_WORLD);
    float min = 999;
    int z;
    for (z = 0; z < num_elements_per_proc; z++)
    {
        if (rand_nums[z] < min)
        {
            min = rand_nums[z];
        }
    }
    float global_min;
    MPI_Reduce(&min, &global_min, 1, MPI_FLOAT, MPI_MIN, 0,
               MPI_COMM_WORLD);
    if (world_rank == 0)
    {
        printf("max is %f\n", global_max);
        printf("min is %f\n", global_min);
    }
    free(rand_nums);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
}