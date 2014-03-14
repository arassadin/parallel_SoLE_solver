#include"sqrtMethod.h"

sqrtMethodSolver::sqrtMethodSolver()
{

}

bool sqrtMethodSolver::systemChecking(int pointer)
{
	bool flag=false;
	for(int i=0; i<systemSize; i++)
		if(matrix[i][pointer]!=std::complex<double>(0.0,0.0))
			flag=true;
	return flag;
}

void sqrtMethodSolver::freeMatrix()
{
	for(int i=0; i<systemSize; i++)
		delete matrix[i];
	delete matrix;
}

void sqrtMethodSolver::freeAllMemory()
{
	freeMatrix();
	delete tmpMatrix;
	delete solve;
}

double* sqrtMethodSolver::getSolve(double** m, int size)
{
	systemSize=size;	
	if(systemSize<2)
	{
		std::cerr << "Bad Matrix Size!" << std::endl;
		return NULL;
	}
	
	matrix=new std::complex<double>*[systemSize];
#pragma omp parallel for
	for(int j=0; j<systemSize; j++)
		matrix[j]=new std::complex<double>[systemSize+1];
#pragma omp parallel for
	for(int i=0; i<systemSize; i++)
#pragma omp parallel for
		for(int j=0; j<systemSize+1; j++)
			matrix[i][j]=std::complex<double>(m[i][j], 0.0);
	
	bool checkingFlag(true);
	for(int j=0; j<systemSize+1; j++)
		if(!systemChecking(j))
		{
			std::cerr << "Non equatable matrix!" << std::endl;
			return NULL;
		}
#pragma omp parallel for shared(checkingFlag)
	for(int i=0; i<systemSize; i++)
	#pragma omp parallel for shared(checkingFlag)
		for(int j=0; j<systemSize; j++)
			if(matrix[i][j]!=matrix[j][i])
			{
				checkingFlag=false;
			}
	if(!checkingFlag)
	{
		std::cerr << "Non symmetrical matrix!" << std::endl;
		freeMatrix();
		return NULL;
	}
	tmpMatrix=new std::complex<double>[systemSize+1];
	matrix[0][0]=pow(matrix[0][0], 0.5);
#pragma omp parallel for
	for(int j=1; j<systemSize+1; j++)
		matrix[0][j]=matrix[0][j]/matrix[0][0];
	for(int i=1; i<systemSize; i++)
	{
#pragma omp parallel for
		for(int j=i; j<systemSize+1; j++)
			tmpMatrix[j]=matrix[i][j];
		std::complex<double> sum(0.0, 0.0);
		for(int k=0; k<i; k++)
		{
			sum+=pow(matrix[k][i], 2.0);
		}
		matrix[i][i]=pow(tmpMatrix[i]-sum, 0.5);
#pragma omp parallel for
		for(int j=i+1; j<systemSize+1; j++)
		{
			std::complex<double> sum(0.0,0.0);
			for(int k=0; k<i; k++)
			{
				sum+=(matrix[k][i]*matrix[k][j]);
			};
			matrix[i][j]=(tmpMatrix[j]-sum)/matrix[i][i];
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
#pragma omp parallel for
	for(int j=0; j<systemSize+1; j++)
		realSolve[j]=solve[j].real();
		
	freeAllMemory();
		
	return realSolve;
}
