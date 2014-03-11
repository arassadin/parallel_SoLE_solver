#include<iostream>
#include<stdio.h>
#include"sqrtMethod.h"
#include"conjugateGradientMethod.h"

using namespace std;
 
int main()
{
	int size;
	cout.precision(4);
	FILE* f=freopen("helpful/input_symmetrical_1000", "r", stdin);
	cin >> size;
	if(size<2)
	{
		cerr << "Bad size!" << endl;
		return -1;
	};
	double** matrix=new double*[size];
	for(int i=0; i<size; i++)
		matrix[i]=new double[size+1];
	for(int i=0; i<size; i++)
		for(int j=0; j<size+1; j++)
			cin>>matrix[i][j];
			
	sqrtMethodSolver* sms=new sqrtMethodSolver();	
	double* x=sms->getSolve(matrix, size);
	for(int j=0; j<size; j++)
		cout << x[j] << "\t";
	cout << endl << "----------------------" << endl;
	
	conjugateGradientSolver* cgs=new conjugateGradientSolver();
	cgs->setAccuracy(0.000001);
	x=cgs->getSolve(matrix, size);
	for(int j=0; j<size; j++)
		cout << x[j] << "\t";
	cout << endl << "----------------------" << endl;
	
    return 0;
}
