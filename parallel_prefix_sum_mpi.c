#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void parallel_prefix_sum(int *arr, int N, int rank, int size) {
    int *temp = (int *)malloc(N * sizeof(int));
    MPI_Scatter(arr, N / size, MPI_INT, temp, N / size, MPI_INT, 0, MPI_COMM_WORLD);

    // Prefix sum within each process
    for (int i = 1; i < N / size; i++) {
        temp[i] += temp[i - 1];
    }

    int offset = 0;
    // Perform a prefix sum across processes
    if (rank != 0) {
        MPI_Recv(&offset, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Add the received prefix sum to each element in the current process's data
    for (int i = 0; i < N / size; i++) {
        temp[i] += offset;
    }

    // Send the last element of each process to the next process
    if (rank != size - 1) {
        MPI_Send(&temp[N / size - 1], 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Gather(temp, N / size, MPI_INT, arr, N / size, MPI_INT, 0, MPI_COMM_WORLD);
    free(temp);
}
int main(int argc, char *argv[]) {
    int rank, size;
    int N;  // Array size (now user input)
    int *arr = NULL;
    double start_time, end_time;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Print the prompt before user input
        printf("Enter the value of N (size of the array): ");
        fflush(stdout);  // Ensure the prompt is printed before input

        // Ask the user to input the value of N
        scanf("%d", &N);

        // Allocate memory for the array
        arr = (int *)malloc(N * sizeof(int));

        // Initialize the array with some values, for example, all 1s
        for (int i = 0; i < N; i++) {
            arr[i] = 1;
        }
    }

    // Broadcast N to all other processes
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Start the timer AFTER user input and array initialization
    MPI_Barrier(MPI_COMM_WORLD);  // Synchronize all processes
    start_time = MPI_Wtime();

    // Perform the parallel prefix sum
    parallel_prefix_sum(arr, N, rank, size);

    // End the timer
    MPI_Barrier(MPI_COMM_WORLD);  // Synchronize all processes again
    end_time = MPI_Wtime();

    // Only the root process prints the execution time
    if (rank == 0) {
        // Print the execution time
        printf("Execution Time: %f seconds\n", end_time - start_time);
    }

    // Free allocated memory
    if (arr) free(arr);

    MPI_Finalize();
    return 0;
}
