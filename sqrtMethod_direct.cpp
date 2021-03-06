#include"sqrtMethod_direct.h"

sqrtMethodSolver_direct::sqrtMethodSolver_direct()
{

}

bool sqrtMethodSolver_direct::systemChecking(int pointer)
{
	bool flag=false;
	for(int i=0; i<systemSize; i++)
		if(matrix[i][pointer]!=std::complex<double>(0.0,0.0))
			flag=true;
	return flag;
}

void sqrtMethodSolver_direct::freeMatrix()
{
	for(int i=0; i<systemSize; i++)
		delete matrix[i];
	delete matrix;
}

void sqrtMethodSolver_direct::freeAllMemory()
{
	freeMatrix();
	delete solve;
}

double* sqrtMethodSolver_direct::getSolve(double** m, int size)
{
	systemSize=size;	
	if(systemSize<2)
	{
		std::cerr << "Bad Matrix Size!" << std::endl;
		return NULL;
	}
	
	matrix=new std::complex<double>*[systemSize];
	for(int j=0; j<systemSize; j++)
		matrix[j]=new std::complex<double>[systemSize+1];
	for(int i=0; i<systemSize; i++)
		for(int j=0; j<systemSize+1; j++)
			matrix[i][j]=std::complex<double>(m[i][j], 0.0);

	for(int j=0; j<systemSize+1; j++)
		if(!systemChecking(j))
		{
			std::cerr << "Non equatable matrix!" << std::endl;
			return NULL;
		}
	for(int i=0; i<systemSize; i++)
		for(int j=0; j<systemSize; j++)
			if(matrix[i][j]!=matrix[j][i])
			{
				std::cerr << "Non symmetrical matrix!" << std::endl;
				freeMatrix();
				return NULL;
			}
			
	for(int i=0; i<systemSize; i++)
	{
		std::complex<double> sum(0.0, 0.0);
		for(int k=0; k<i; k++)
		{
			sum+=pow(matrix[k][i], 2.0);
		}
		matrix[i][i]=pow(m[i][i]-sum, 0.5);
		for(int j=i+1; j<systemSize+1; j++)
		{
			std::complex<double> sum(0.0,0.0);
			for(int k=0; k<i; k++)
			{
				sum+=(matrix[k][i]*matrix[k][j]);
			};
			matrix[i][j]=(m[i][j]-sum)/matrix[i][i];
		}
	}
	
	solve=new std::complex<double>[systemSize];
	for(int i=systemSize-1; i>=0; i--)
	{
		std::complex<double> sum(0.0,0.0);
		for(int k=i+1; k<systemSize; k++)
			sum+=matrix[i][k]*solve[k];
		solve[i]=(matrix[i][systemSize]-sum)/matrix[i][i];
	}
	
	double* realSolve=new double[systemSize+1];
	for(int j=0; j<systemSize+1; j++)
		realSolve[j]=solve[j].real();
		
	freeAllMemory();
		
	return realSolve;
}
