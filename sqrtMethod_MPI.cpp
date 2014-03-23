#include"sqrtMethod_MPI.h"
#include<unistd.h>

sqrtMethodSolver_MPI::sqrtMethodSolver_MPI()
{

}

bool sqrtMethodSolver_MPI::systemChecking(int pointer)
{
	bool flag=false;
	for(int i=0; i<systemSize; i++)
		if(matrix[i][pointer]!=std::complex<double>(0.0,0.0))
			flag=true;
	return flag;
}

void sqrtMethodSolver_MPI::freeMatrix()
{
	for(int i=0; i<systemSize; i++)
		delete matrix[i];
	delete matrix;
}

void sqrtMethodSolver_MPI::freeAllMemory()
{
	freeMatrix();
	delete solve;
}

double* sqrtMethodSolver_MPI::getSolve(double** m, int size)
{	
	systemSize=size;	
	if(systemSize<2)
	{
		std::cerr << "Bad Matrix Size!" << std::endl;
		return NULL;
	}
	
	int currRank, rankQ(1), jobFraction(1);
	double* realSolve;
	
	MPI_Init(NULL, NULL);
	
	MPI_Comm_size(MPI_COMM_WORLD, &rankQ);
	MPI_Comm_rank(MPI_COMM_WORLD, &currRank); 
	
	std::cout << "ranks: " << currRank << std::endl;
	
	matrix=new std::complex<double>*[systemSize];
	for(int j=0; j<systemSize; j++)
		matrix[j]=new std::complex<double>[systemSize+1];
	for(int i=0; i<systemSize; i++)
		for(int j=0; j<systemSize+1; j++)
			matrix[i][j]=std::complex<double>(m[i][j], 0.0);
	
	if(currRank==0)
	{
	
	bool checkingFlag(true);
	for(int j=0; j<systemSize+1; j++)
		if(!systemChecking(j))
		{
			std::cerr << "Non equatable matrix!" << std::endl;
			freeMatrix();
			MPI_Finalize();
			return NULL;
		}
	for(int i=0; i<systemSize; i++)
		for(int j=0; j<systemSize; j++)
			if(matrix[i][j]!=matrix[j][i])
			{
				checkingFlag=false;
			}
	if(!checkingFlag)
	{
		std::cerr << "Non symmetrical matrix!" << std::endl;
		freeMatrix();
		MPI_Finalize();
		return NULL;
	}
	
	}
		matrix[0][0]=pow(matrix[0][0], 0.5);
	
	if(rankQ<=systemSize)
		jobFraction=(systemSize+1)/(rankQ-1);
	if(jobFraction*(rankQ-1)<systemSize)
		jobFraction++;
	//std::cout << "fraction: " << jobFraction << std::endl;
	
	if(currRank==0)
	{
		MPI_Status s;
		for(int j=1; j<systemSize+1; j++)
			MPI_Recv(&matrix[0][j], 1, MPI_COMPLEX, MPI_ANY_SOURCE, j, MPI_COMM_WORLD, &s);
	}
	else
	{
		for(int j=0; j<jobFraction; j++)
			if((currRank-1)*jobFraction+j < systemSize+1 && (currRank-1)*jobFraction+j != 0)
			{
				//std::cout << "happend: " << (currRank-1)*jobFraction+j << std::endl;
				matrix[0][(currRank-1)*jobFraction+j]/=matrix[0][0];
				MPI_Send(&matrix[0][(currRank-1)*jobFraction+j], 1, MPI_COMPLEX, 0, (currRank-1)*jobFraction+j, MPI_COMM_WORLD);
			}
	}
		
	if(currRank==0)
	{
		/*for(int j=0; j<systemSize+1; j++)
			std::cout << matrix[0][j] << " ";
		std::cout << std::endl;*/
	
	for(int i=1; i<systemSize; i++)
	{
		std::complex<double> sum(0.0, 0.0);
		for(int k=0; k<i; k++)
		{
			sum+=pow(matrix[k][i], 2.0);
		}
		matrix[i][i]=pow(m[i][i]-sum, 0.5);
		for(int j=i+1; j<systemSize+1; j++)
		{
			std::complex<double> sum(0.0, 0.0);
			for(int k=0; k<i; k++)
			{
				sum+=(matrix[k][i]*matrix[k][j]);
			}
			matrix[i][j]=(m[i][j]-sum)/matrix[i][i];
		}
	}
	
	}
	
	//if(rankQ<systemSize)
		jobFraction=(systemSize)/(rankQ);
	if(jobFraction*(rankQ)<systemSize)
		jobFraction++;
	
	if(currRank==0)
	{
		solve=new std::complex<double>[systemSize];
		for(int i=systemSize-1; i>=0; i--)
		{
			std::complex<double> sum(0.0,0.0);
			for(int k=i+1; k<systemSize; k++)
			{
				sum+=matrix[i][k]*solve[k];
			}
			solve[i]=(matrix[i][systemSize]-sum)/matrix[i][i];
		}
	}
	
	//std::cout << "Here " << currRank << std::endl;
	
	if(currRank==0)
	{
		realSolve=new double[systemSize+1];
		for(int j=0; j<systemSize+1; j++)
			realSolve[j]=solve[j].real();
		
		freeAllMemory();
		MPI_Finalize();
		return realSolve;
	}
	else
	{
		freeAllMemory();
		MPI_Finalize();
	}
}
