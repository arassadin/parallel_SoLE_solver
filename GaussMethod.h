#include <iostream>

class GaussMethodSolver
{
public:
	GaussMethodSolver();
	~GaussMethodSolver();
	double* getSolve(double**, int);
		
private:
	int size;
	double** A;
	double* solve;
};

