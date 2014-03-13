#include<iostream>
#include<stdio.h>
#include<time.h>
#include"sqrtMethod.h"
#include"conjugateGradientMethod.h"

using namespace std;
 
int main()
{
	int size;
	unsigned int time_before, time_after;
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
	time_before=time(NULL);	
	double* x=sms->getSolve(matrix, size);
	time_after=time(NULL);
	cout << "time: " << time_after-time_before << endl;
	for(int j=0; j<size; j++)
		cout << x[j] << "\t";
	cout << endl << "----------------------" << endl;
	
	/*conjugateGradientSolver* cgs=new conjugateGradientSolver();
	cgs->setAccuracy(0.000001);
	x=cgs->getSolve(matrix, size);
	for(int j=0; j<size; j++)
		cout << x[j] << "\t";
	cout << endl << "----------------------" << endl;*/
	
    return 0;
}
