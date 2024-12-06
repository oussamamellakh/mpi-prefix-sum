# Makefile for building the MPI-based Parallel Prefix Sum program

# Compiling the file
mpicc -o prefix_sum parallel_prefix_sum_mpi.c

# Running the file
mpirun -np 4 ./prefix_sum
