#include "GaussianMethod_OpenMP.h"

GaussianMethodSolver_OpenMP:: GaussianMethodSolver_OpenMP() { }

GaussianMethodSolver_OpenMP:: ~GaussianMethodSolver_OpenMP()
{	
	delete [] solve;
	
	for (int i = 0; i < size; i++)
 	{
    	delete [] A[i];
 	}
 	delete [] A;
}

double* GaussianMethodSolver_OpenMP:: getSolve(double** Matrix, int SizeSystem)
{		
		size = SizeSystem;
		double** A = new double*[size];
		#pragma omp parallel for
        for(int i=0;i<size;++i)
				A[i]=new double[size+1];
	    #pragma omp parallel for  
		for(int i=0; i<size; i++)
		#pragma omp parallel for
			for(int j=0; j<size+1; j++)
				A[i][j]=Matrix[i][j];
				
		double* solve = new double[size];
		double temp;
		
		double beforeTime=omp_get_wtime();
		
		/// direct step
		int j;
		int k;
		int i;
		for(i=0;i<size;i++)
		   {
		   #pragma omp parallel for private(j,k,temp) shared(i)
		   for(j=i+1;j<size;j++)
			  {
				 temp = (A[j][i])/(A[i][i]);
			  for(k=0; k<size+1;k++)
	   			 {
					A[j][k]=A[j][k]-A[i][k]*temp;
	   			 }
	 	      }
		}
       	//  reverse step
       	        solve[size-1] = A[size-1][size]/A[size-1][size-1];	
				for(int i=size-2;i>=0;i--)
				{
					temp=0;
					#pragma omp parallel for reduction(+:temp) shared(i) private(j) 
	  				for(j=i+1;j<size;j++)
	  				{
	  					temp = temp + A[i][j]*solve[j];
	  				}
	   				temp = A[i][size] - temp;
	   				solve[i] = temp/A[i][i];
				}
				double afterTime=omp_get_wtime();
	std::cout << "Algo time: " << afterTime-beforeTime << std::endl;	
    return solve;
} 

