#include<iostream>
#include"matrixSolver.h"

using namespace std;

int main()
{
	double** m1=new double*[3];
	for(int i=0; i<3; i++)
		m1[i]=new double[2];
		
	m1[0][0]=2; m1[0][1]=5;
	m1[1][0]=3; m1[1][1]=6;
	m1[2][0]=1; m1[2][1]=7;
	
	double** m2=new double*[2];
	for(int i=0; i<2; i++)
		m2[i]=new double[3];
		
	m2[0][0]=3; m2[0][1]=9; m2[0][2]=4;
	m2[1][0]=8; m2[1][1]=5; m2[1][2]=2;
	
	double** m3=new double*[2];
	for(int i=0; i<2; i++)
		m3[i]=new double[3];
		
	m3[0][0]=4; m3[0][1]=5; m3[0][2]=1;
	m3[1][0]=9; m3[1][1]=3; m3[1][2]=2;
	
	m_size s1, s2, s3;
	s1.vert=3; s1.hor=2;
	s2.vert=2; s2.hor=3;
	s3=s2;
	
	matrixSolver* ms=new matrixSolver();
	
	double** res=ms->multiply(m1, s1, m2, s2);
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
			cout << res[i][j] << "\t";
		cout << endl;
	}
	
	cout << endl;
	
	double** res2=ms->transponate(m1, s1);
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
			cout << res2[i][j] << "\t";
		cout << endl;
	}
	
	cout << endl;
	
	double** res3=ms->divide(m2, m3, s2);
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
			cout << res3[i][j] << "\t";
		cout << endl;
	}

}
