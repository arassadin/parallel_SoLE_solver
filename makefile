CCSHELL=/bin/bash
CC=g++
MPI_CC=mpic++
DIRECT_BUILD_FLAGS=-o psdirect
OPENMP_BUILD_FLAGS=-fopenmp -o psopenmp
MPI_BUILD_FLAGS=-o psmpi
CUR_DIRECTORY=$(shell pwd)
MATRIX_SOLVER_DIR=helpful/matrixes

all: direct openmp mpi

direct:
	export PARALLEL_SOLVER_VERSION=0
	$(CC) test.cpp conjugateGradientMethod_direct.cpp sqrtMethod_direct.cpp $(MATRIX_SOLVER_DIR)/matrixSolver.cpp $(DIRECT_BUILD_FLAGS)

openmp:
	export PARALLEL_SOLVER_VERSION=1
	$(CC) test.cpp conjugateGradientMethod_OpenMP.cpp sqrtMethod_OpenMP.cpp $(MATRIX_SOLVER_DIR)/matrixSolver.cpp $(OPENMP_BUILD_FLAGS)
	
mpi:
	export PARALLEL_SOLVER_VERSION=2
	$(MPI_CC) test.cpp conjugateGradientMethod_MPI.cpp sqrtMethod_MPI.cpp $(MATRIX_SOLVER_DIR)/matrixSolver.cpp $(MPI_BUILD_FLAGS)

clean:
	rm *~ *.out psdirect psopenmp psmpi
