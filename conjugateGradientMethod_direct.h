#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>
#include"helpful/matrixes/matrixSolver.h"

class conjugateGradientSolver_direct
{
public:
	conjugateGradientSolver_direct();
	double* getSolve(double**, int);
	void setAccuracy(double);
	~conjugateGradientSolver_direct();
	
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
