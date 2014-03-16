#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>
#include"helpful/matrixes/matrixSolver.h"

class conjugateGradientSolver_MPI
{
public:
	conjugateGradientSolver_MPI();
	double* getSolve(double**, int);
	void setAccuracy(double);
	~conjugateGradientSolver_MPI();
	
private:
	int systemSize;
	double** matrix;
	double** constantTerms;
	double accuracy;

private:
	bool systemChecking(int);
	void freeMemory();
	bool stopCondition(double**);
};
