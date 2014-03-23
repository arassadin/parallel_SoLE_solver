#include <iostream>

class GaussianMethodSolver_direct
{
public:
	GaussianMethodSolver_direct();
	~GaussianMethodSolver_direct();
	double* getSolve(double**, int);
		
private:
	int size;
	double** A;
	double* solve;
};

