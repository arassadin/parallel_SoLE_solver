#include "GaussMethod.h"

GaussMethodSolver:: GaussMethodSolver() { }

GaussMethodSolver:: ~GaussMethodSolver()
{	
	delete [] solve;
	
	for (int i = 0; i < size; i++)
 	{
    	delete [] A[i];
 	}
 	delete [] A;
}

double* GaussMethodSolver:: getSolve(double** Matrix, int SizeSystem)
{		
		size = SizeSystem;
		double** A = new double*[size];
        for(int i=0;i<size;++i)
				A[i]=new double[size+1];
	      
		for(int i=0; i<size; i++)
			for(int j=0; j<size+1; j++)
				A[i][j]=Matrix[i][j];
				
		double* solve = new double[size];
		double temp;
		
		/// direct step
		for(int i=0;i<size;i++)
		   {
		   for(int j=i+1;j<size;j++)
			  {
				 temp = (A[j][i])/(A[i][i]);
			  for(int k=0; k<size+1;k++)
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
	  				for(int j=i+1;j<size;j++)
	  				{
	  					temp = temp + A[i][j]*solve[j];
	  				}
	   				temp = A[i][size] - temp;
	   				solve[i] = temp/A[i][i];
				}	
    return solve;
} 

