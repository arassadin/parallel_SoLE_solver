CCSHELL=/bin/bash
CC=g++
DIRECT_BUILD_FLAGS=-o psdirect
OPENMP_BUILD_FLAGS=-fopenmp -o psopenmp
MPI_BUILD_FLAGS=""
CUR_DIRECTORY=$(shell pwd)
MATRIX_SOLVER_DIR=helpful/matrixes

all: direct openmp mpi

direct: 
	$(CC) test.cpp conjugateGradientMethod_direct.cpp sqrtMethod_direct.cpp $(MATRIX_SOLVER_DIR)/matrixSolver.cpp $(DIRECT_BUILD_FLAGS)

openmp: 
	$(CC) test.cpp conjugateGradientMethod_direct.cpp sqrtMethod_OpenMP.cpp $(MATRIX_SOLVER_DIR)/matrixSolver.cpp $(OPENMP_BUILD_FLAGS)
	
mpi:

clean:
	rm *~ *.out psdirect psopenmp psmpi
