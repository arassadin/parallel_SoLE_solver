#include<iostream>
#include<math.h>
#include"matrix_size.h"

class matrixSolver
{
public:
	double** multiply(double**, m_size, double**, m_size);
	double sMultiply(double**, double**, m_size);
	double** sMultiply(double, double**, m_size);
	double** transponate(double**, m_size);
	double** transponate(double*, int);
	double** divide(double**, double**, m_size);
	double** summ(double**, double**, m_size);
};
