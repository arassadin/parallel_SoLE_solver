#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>
#include<omp.h>

class sqrtMethodSolver_OpenMP
{
public:
	sqrtMethodSolver_OpenMP();
	double* getSolve(double**, int);
	~sqrtMethodSolver_OpenMP();
	
private:
	int systemSize;
	std::complex<double>** matrix;
	std::complex<double>* solve;

private:
	bool systemChecking(int);
	void freeMatrix();
	void freeAllMemory();
};
