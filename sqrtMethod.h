#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>

class sqrtMethodSolver
{
public:
	sqrtMethodSolver(double**, int);
	double* getSolve();
	~sqrtMethodSolver();
	
private:
	int systemSize;
	std::complex<double>** matrix;
	std::complex<double>* tmpMatrix;
	std::complex<double>* solve;

private:
	bool systemChecking(int);
	void freeMemory();
};
