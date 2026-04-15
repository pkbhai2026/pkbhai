#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <assert.h>
#include <time.h>

int *create_rand_nums(int num_elements)
{
    int *rand_nums = (int *)malloc(sizeof(int) * num_elements);
    assert(rand_nums != NULL);

    for (int i = 0; i < num_elements; i++)
    {
        rand_nums[i] = rand() % 1000;
    }
    return rand_nums;
}

int main(int argc, char **argv)
{
    MPI_Init(NULL, NULL);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int total_elements = 1000;
    int num_elements_per_proc = total_elements / world_size;

    srand(time(NULL) + world_rank);

    int *rand_nums = create_rand_nums(num_elements_per_proc);

    int local_sum = 0;

    for (int i = 0; i < num_elements_per_proc; i++)
    {
        if (rand_nums[i] % 2 != 0)
        {
            local_sum += rand_nums[i];
        }
    }

    printf("Process %d: Local odd sum = %d\n", world_rank, local_sum);

    int global_sum;

    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

    if (world_rank == 0)
    {
        printf("\nTotal sum of odd numbers = %d\n", global_sum);
    }

    free(rand_nums);
    MPI_Finalize();

    return 0;
}