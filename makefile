CCSHELL=/bin/bash
CC=g++
CUR_DIRECTORY=$(shell pwd)
MATRIX_SOLVER_DIRECTORY=../../useful/matrixes

all: build

build:
	$(CC) test.cpp conjugateGradientMethod.cpp sqrtMethod.cpp $(MATRIX_SOLVER_DIRECTORY)/matrixSolver.cpp -fopenmp

clean:
	rm *~ *.out
