#include"conjugateGradientMethod_MPI.h"

conjugateGradientSolver_MPI::conjugateGradientSolver_MPI()
{
	accuracy=0.0001;
}

void conjugateGradientSolver_MPI::setAccuracy(double _accuracy)
{
	accuracy=_accuracy;
}

bool conjugateGradientSolver_MPI::systemChecking(int pointer)
{
	bool flag=false;
	for(int i=0; i<systemSize; i++)
		if(matrix[i][pointer]!=0.0)
			flag=true;
	return flag;
}

void conjugateGradientSolver_MPI::freeMemory()
{
	for(int i=0; i<systemSize; i++)
		delete[] matrix[i];
	delete matrix;
}

bool conjugateGradientSolver_MPI::stopCondition(double** _discrepancy)
{
	bool status(true);
	for(int i=0; i<systemSize; i++)
		if(_discrepancy[i][0]>=accuracy)
			status=false;
	return status;
}

double* conjugateGradientSolver_MPI::getSolve(double** m, int size)
{
	systemSize=size;
	matrix=new double*[systemSize];
	for(int i=0; i<systemSize; i++)
		matrix[i]=new double[systemSize];
	for(int i=0; i<systemSize; i++)
		for(int j=0; j<systemSize; j++)
			matrix[i][j]=m[i][j];
	constantTerms=new double*[systemSize];
	for(int i=0; i<systemSize; i++)
		constantTerms[i]=new double[1];
	for(int i=0; i<systemSize; i++)
		constantTerms[i][0]=m[i][systemSize];
		
	if(systemSize<2)
	{
		std::cerr << "Bad systemSize!" << std::endl;
		return NULL;
	};
	for(int j=0; j<systemSize+1; j++)
		if(!systemChecking(j))
		{
			std::cerr << "Non equatable matrix!" << std::endl;
			return NULL;
		};
	for(int i=0; i<systemSize; i++)
		for(int j=0; j<systemSize; j++)
			if(matrix[i][j]!=matrix[j][i])
			{
				std::cerr << "Non symmetrical matrix!" << std::endl;
				return NULL;
			};
	double** prevSolve=new double*[systemSize];
	for(int i=0; i<systemSize; i++)
		prevSolve[i]=new double[1];
	prevSolve[0][0]=1.0;
	for(int i=1; i<systemSize; i++)
		prevSolve[i][0]=0.0;
	
	matrixSolver* ms=new matrixSolver();
	m_size matrixSize, solveSize;
	matrixSize.hor=systemSize; matrixSize.vert=systemSize;
	solveSize.hor=1; solveSize.vert=systemSize;
	
	/*std::cout << "**************************************" << std::endl;*/
	
	double** tmp1=ms->multiply(matrix, matrixSize, prevSolve, solveSize);
	double** discrepancy=ms->divide(constantTerms, tmp1, solveSize);
	double** currDirection=discrepancy;
	double** tmp2=ms->multiply(matrix, matrixSize, currDirection, solveSize);
	double alpha=ms->sMultiply(discrepancy, discrepancy, solveSize)/ms->sMultiply( currDirection, tmp2, solveSize );
	double** solveCorrection=ms->sMultiply(alpha, currDirection, solveSize);
	double** currSolve=ms->summ(prevSolve, solveCorrection, solveSize);
	
	while(!stopCondition(discrepancy))
	{
		/*for(int i=0; i<systemSize; i++)
			std::cout << currSolve[i][0] << "\t";
		std::cout << std::endl << "**************************************" << std::endl;*/
		
		double** prevDirection=currDirection;
		prevSolve=currSolve;
		
		tmp1=ms->multiply(matrix, matrixSize, prevSolve, solveSize);
		/*std::cout << "tmp1: ";
		for(int i=0; i<systemSize; i++)
			std::cout << tmp1[i][0] << "\t";
		std::cout << std::endl;*/
		
		discrepancy=ms->divide(constantTerms, tmp1, solveSize);
		/*std::cout << "discrepancy: ";
		for(int i=0; i<systemSize; i++)
			std::cout << discrepancy[i][0] << "\t";
		std::cout << std::endl;*/
		
		tmp2=ms->multiply(matrix, matrixSize, prevDirection, solveSize);
		/*std::cout << "tmp2: ";
		for(int i=0; i<systemSize; i++)
			std::cout << tmp2[i][0] << "\t";
		std::cout << std::endl;*/
		
		double beta=-ms->sMultiply(discrepancy, tmp2, solveSize)/ms->sMultiply(prevDirection, tmp2, solveSize);
		/*std::cout << beta << std::endl;*/
		
		currDirection=ms->summ(discrepancy, ms->sMultiply(beta, prevDirection, solveSize), solveSize);
		/*std::cout << "currDirection: ";
		for(int i=0; i<systemSize; i++)
			std::cout << currDirection[i][0] << "\t";
		std::cout << std::endl;*/
		
		double** tmp3=ms->multiply(matrix, matrixSize, currDirection, solveSize);
		/*std::cout << "tmp3: ";
		for(int i=0; i<systemSize; i++)
			std::cout << tmp3[i][0] << "\t";
		std::cout << std::endl;*/
		
		alpha=ms->sMultiply(discrepancy, currDirection, solveSize)/ms->sMultiply(currDirection, tmp3, solveSize);
		/*std::cout << alpha << std::endl;*/
		
		solveCorrection=ms->sMultiply(alpha, currDirection, solveSize);
		/*std::cout << "solveCorrection: ";
		for(int i=0; i<systemSize; i++)
			std::cout << solveCorrection[i][0] << "\t";
		std::cout << std::endl;*/
		
		currSolve=ms->summ(prevSolve, solveCorrection, solveSize);
	}
	
	double* solve=new double[systemSize];
	for(int j=0; j<systemSize; j++)
		solve[j]=currSolve[j][0];
	return solve;
}
