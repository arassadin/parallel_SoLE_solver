#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>

class sqrtMethodSolver_direct
{
public:
	sqrtMethodSolver_direct();
	double* getSolve(double**, int);
	~sqrtMethodSolver_direct();
	
private:
	int systemSize;
	std::complex<double>** matrix;
	std::complex<double>* solve;

private:
	bool systemChecking(int);
	void freeMatrix();
	void freeAllMemory();
};
