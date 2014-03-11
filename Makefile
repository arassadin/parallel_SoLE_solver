CCSHELL=/bin/bash
CC=g++
OPENMP = -fopenmp
CUR_DIRECTORY=$(shell pwd)
GAUSS_DIR=$(CUR_DIRECTORY)/gaussMethod
SQRT_DIR=$(CUR_DIRECTORY)/sqrtMethod
CONJ_GRAD_DIR=$(CUR_DIRECTORY)/conjugateGradientMethod
all: direct

direct: 
	$(CC) main.cpp $(CONJ_GRAD_DIR)/conjugateGradientMethod.cpp  $(CONJ_GRAD_DIR)/matrix/matrixSolver.cpp $(SQRT_DIR)/sqrtMethod.cpp $(GAUSS_DIR)/GaussMethod.cpp  

gauss:
	$(CC) main.cpp $(GAUSS_DIR)/GaussMethod.cpp
sqrtMet:
	$(CC) main.cpp $(SQRT_DIR)/sqrtMethod.cpp
conjugateGradient:
	$(CC) main.cpp $(CONJ_GRAD_DIR)/conjugateGradientMethod.cpp  $(CONJ_GRAD_DIR)/matrix/matrixSolver.cpp

openmp: 
	$(CC) main.cpp $(CONJ_GRAD_DIR)/conjugateGradientMethod.cpp  $(CONJ_GRAD_DIR)/matrix/matrixSolver.cpp $(SQRT_DIR)/sqrtMethod.cpp $(GAUSS_DIR)/GaussMethod.cpp -fopenmp
	
mpi:

clean: 
	rm -f *.o *~ *.out 
	
	
	
	
	
	
	
#
#
	#sqrtMethod conjugateGradientMethod   	
	#sqrtMethod:
#	$(CC) main.cpp conjugateGradientMethod.cpp
#conjugateGradientMethod:
#	$(CC) main.cpp sqrtMethod.cpp
###
#openmp: gaussMethod sqrtMethod conjugateGradientMethod
#
#gaussMethod: 
#	$(CC) main.cpp GaussMethod.cpp $(OPENMP)
#sqrtMethod:
#	$(CC) main.cpp conjugateGradientMethod.cpp 	$(OPENMP)
#conjugateGradientMethod:
#	$(CC) main.cpp sqrtMethod.cpp	$(OPENMP)
###
#mpi:

#
	

#CC=g++
#CUR_DIRECTORY=$(shell pwd)
#MATRIX_SOLVER_DIRECTORY=../../useful/matrixes

#all: build

#build:
#	$(CC) test.cpp conjugateGradientMethod.cpp sqrtMethod.cpp $(MATRIX_SOLVER_DIRECTORY)/matrixSolver.cpp

#clean:
#	rm *~ *.out
