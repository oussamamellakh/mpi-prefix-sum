# MPI Parallel Prefix Sum

This repository contains an implementation of a parallel prefix sum using MPI.

## Features
- Efficient prefix sum computation for large arrays distributed across multiple processes.
- Example array initialization with all elements set to 1.
- Measures execution time of the operation.

## Prerequisites
- MPI library (e.g., OpenMPI or MPICH)
- C compiler supporting MPI (e.g., `mpicc`)

## Files
- `parallel_prefix_sum.c`: Source code for the MPI prefix sum.
- `Makefile`: Instructions to build the program.

## Build Instructions
1. Ensure you have an MPI environment set up.
2. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/Mpi-prefix-sum.git
   cd mpi-prefix-sum
