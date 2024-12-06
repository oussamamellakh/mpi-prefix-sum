## Compile the file
mpicc -o prefix_sum parallel_prefix_sum_mpi.c

## Run the file
mpirun -np 4 ./prefix_sum
