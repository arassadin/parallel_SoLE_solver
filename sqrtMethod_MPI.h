#include<iostream>
#include<complex>
#include<math.h>
#include<stdio.h>
//#include<mpi.h>

class sqrtMethodSolver_MPI
{
public:
	sqrtMethodSolver_MPI();
	double* getSolve(double**, int);
	~sqrtMethodSolver_MPI();
	
private:
	int systemSize;
	std::complex<double>** matrix;
	std::complex<double>* tmpMatrix;
	std::complex<double>* solve;

private:
	bool systemChecking(int);
	void freeMatrix();
	void freeAllMemory();
};
