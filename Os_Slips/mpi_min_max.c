#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#define MAX 1000

int main(int argc, char *argv[]) {
    int rank, size;
    int localArray[MAX];
    int minLocal, minGlobal;
    int maxLocal, maxGlobal;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    srand(rank); // Seed based on rank

    for (int i = 0; i < MAX; i++) { // Start from 0
        localArray[i] = rand() % 100;
    }

    // Find the minimum number in the local array
    minLocal = localArray[0];
    for (int i = 1; i < MAX; i++) { // Start from 1
        if (localArray[i] < minLocal) {
            minLocal = localArray[i];
        }
    }

    // Find the maximum number in the local array
    maxLocal = localArray[0];
    for (int i = 1; i < MAX; i++) { // Start from 1
        if (localArray[i] > maxLocal) {
            maxLocal = localArray[i];
        }
    }

    // Use MPI_Reduce to find the global minimum
    MPI_Reduce(&minLocal, &minGlobal, 1, MPI_INT, MPI_MIN, 0, MPI_COMM_WORLD);
    // Use MPI_Reduce to find the global maximum
    MPI_Reduce(&maxLocal, &maxGlobal, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global minimum: %d\n", minGlobal);
        printf("Global maximum: %d\n", maxGlobal);
    }

    MPI_Finalize();

    return 0;
}
