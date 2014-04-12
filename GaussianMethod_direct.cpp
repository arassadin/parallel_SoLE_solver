#include "GaussianMethod_direct.h"

GaussianMethodSolver_direct:: GaussianMethodSolver_direct() { }

GaussianMethodSolver_direct:: ~GaussianMethodSolver_direct()
{	
	delete [] solve;
	
	for (int i = 0; i < size; i++)
 	{
    	delete [] A[i];
 	}
 	delete [] A;
}

double* GaussianMethodSolver_direct:: getSolve(double** Matrix, int SizeSystem)
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
		unsigned int start_time =  clock();
		
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
	unsigned int end_time = clock(); // конечное время
    unsigned int search_time = end_time - start_time; // искомое время
    std::cout << "Algo time direct: "<<((float)search_time) / CLOCKS_PER_SEC  <<std::endl;
				
    return solve;
} 

