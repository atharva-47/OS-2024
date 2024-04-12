#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define ARRAY_SIZE 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int local_array[ARRAY_SIZE];
    int global_sum = 0;
    int local_sum = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    // Initialize random number generator
    srand(rank);
    
    // Generate random numbers for local array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_array[i] = rand() % 100; // Generate random numbers between 0 and 99
    }
    
    // Calculate local sum
    for (int i = 0; i < ARRAY_SIZE; i++) {
        local_sum += local_array[i];
    }
    
    // Perform global sum reduction
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    
    // Output result from root process
    if (rank == 0) {
        printf("Total sum: %d\n", global_sum);
    }
    
    MPI_Finalize();
    return 0;
}
