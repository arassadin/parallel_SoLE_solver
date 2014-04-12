#include <iostream>
#include <omp.h>
class GaussianMethodSolver_OpenMP
{
public:
	GaussianMethodSolver_OpenMP();
	~GaussianMethodSolver_OpenMP();
	double* getSolve(double**, int);

private:
	int size;
	double** A;
	double* solve;
};

