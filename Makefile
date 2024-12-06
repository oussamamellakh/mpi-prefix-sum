# Makefile for building the MPI-based Parallel Prefix Sum program

# Compiler to use
CC = mpicc

# Compiler flags: 
# -O2 optimizes for speed
# -Wall enables all warnings
CFLAGS = -O2 -Wall

# Name of the target executable
TARGET = parallel_prefix_sum

# Default rule to build the program
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Rule to clean up generated files
clean:
	rm -f $(TARGET)
