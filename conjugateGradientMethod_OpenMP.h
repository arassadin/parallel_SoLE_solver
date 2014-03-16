#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>
#include"helpful/matrixes/matrixSolver.h"

class conjugateGradientSolver_OpenMP
{
public:
	conjugateGradientSolver_OpenMP();
	double* getSolve(double**, int);
	void setAccuracy(double);
	~conjugateGradientSolver_OpenMP();
	
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
