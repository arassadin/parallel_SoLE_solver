#include<iostream>
#include<stdio.h>
#include<stdlib.h>

#define SIZE 1000

using namespace std;

int main()
{
	double** matrix=new double*[SIZE];
	for(int i=0; i<SIZE; i++)
		matrix[i]=new double[SIZE];
	for(int i=0; i<SIZE; i++)
	{
		matrix[i][i]=rand()%10+1;
		for(int j=i+1; j<SIZE; j++)
		{
			matrix[i][j]=rand()%10+1+(rand()%1000)/1000.0;
			matrix[j][i]=matrix[i][j];
		}
	}
	FILE* f=freopen("input_symmetrical", "w", stdout);
	cout << SIZE << endl;
	for(int i=0; i<SIZE; i++)
	{
		double sum(0.0);
		for(int j=0; j<SIZE; j++)
		{
			sum+=matrix[i][j];
			cout << matrix[i][j] << "\t";
		}
		cout << sum << endl;
	}
}
