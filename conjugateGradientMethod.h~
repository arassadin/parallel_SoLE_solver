#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>
#include"helpful/matrixes/matrixSolver.h"

class conjugateGradientSolver
{
public:
	conjugateGradientSolver(double**, int);
	double* getSolve();
	void setAccuracy(double);
	~conjugateGradientSolver();
	
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
