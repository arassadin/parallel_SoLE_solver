#include"matrixSolver.h"

double** matrixSolver::multiply(double** m1, m_size size_m1, double** m2, m_size size_m2)
{
	double** result;
	if(size_m1.hor==size_m2.vert)
	{
		result=new double*[size_m1.vert];
		for(int i=0; i<size_m1.vert; i++)
			result[i]=new double[size_m2.hor];
		for(int j=0; j<size_m2.hor; j++)
		{
			for(int i=0; i<size_m1.vert; i++)
			{
				double tmp_res=0.0;
				for(int k=0; k<size_m2.vert; k++)
				{
					tmp_res+=m1[i][k]*m2[k][j];
				}
				result[i][j]=tmp_res;
			}
		}
	}
	else
	{
		result=NULL;
	}
		
	return result;
}

double matrixSolver::sMultiply(double** m1, double** m2, m_size s)
{
	double result(0.0);
	for(int i=0; i<s.vert; i++)
	{
		result+=m1[i][0]*m2[i][0];
	}
		
	return result;
}

double** matrixSolver::sMultiply(double n, double** m, m_size s)
{
	double** result=new double*[s.vert];
	for(int i=0; i<s.vert; i++)
		result[i]=new double[s.hor];
	for(int i=0; i<s.vert; i++)
	{
		for(int j=0; j<s.hor; j++)
			result[i][j]=n*m[i][j];
	}
	
	return result;
}

double** matrixSolver::transponate(double** m, m_size s)
{
	double** result=new double*[s.hor];
	for(int i=0; i<s.hor; i++)
		result[i]=new double[s.vert];
	for(int i=0; i<s.hor; i++)
		for(int j=0; j<s.vert; j++)
			result[i][j]=m[j][i];
	return result;
}

double** matrixSolver::transponate(double* m, int s)
{
	double** result=new double*[s];
	for(int i=0; i<s; i++)
		result[i]=new double[1];
	for(int i=0; i<s; i++)
			result[i][0]=m[i];
	return result;
}

double** matrixSolver::divide(double** m1, double** m2, m_size s)
{
	double** result;
	result=new double*[s.vert];
	for(int i=0; i<s.vert; i++)
	{
		result[i]=new double[s.hor];
		for(int j=0; j<s.hor; j++)
			result[i][j]=m1[i][j]-m2[i][j];
	}
	return result;
}

double** matrixSolver::summ(double** m1, double** m2, m_size s)
{
	double** result;
	result=new double*[s.vert];
	for(int i=0; i<s.vert; i++)
	{
		result[i]=new double[s.hor];
		for(int j=0; j<s.hor; j++)
			result[i][j]=m1[i][j]+m2[i][j];
	}
	return result;
}
