CCSHELL=/bin/bash
CC=g++
CUR_DIRECTORY=$(shell pwd)
MATRIX_SOLVER_DIR=helpful/matrixes

all: direct openmp mpi

direct: 
	$(CC) test.cpp conjugateGradientMethod_direct.cpp sqrtMethod_direct.cpp $(MATRIX_SOLVER_DIR)/matrixSolver.cpp -o psdirect

openmp: 
	$(CC) test.cpp conjugateGradientMethod_direct.cpp sqrtMethod_OpenMP.cpp $(MATRIX_SOLVER_DIR)/matrixSolver.cpp -fopenmp -o psopenmp
	
mpi:

clean:
	rm *~ *.out psdirect psopenmp psmpi
