#pragma once
//THIS CLASS IS NOT OURS. We are allowed to use it and distribute it for free under the Code Project Open Licencse: https://www.codeproject.com/info/cpol10.aspx.
//Source: https://www.codeproject.com/Articles/25237/Bezier-Curves-Made-Simple by Tolga Birdal
//This class is needed to connect procedurally generated lines to create fish and terrain. Due to time, we used this instead of creating our own curve fitting system.

#include <math.h>
#include <stdlib.h>
#include <vector>

class Bezier
{
private:
	double* FactorialLookup;

	double factorial(int n);
	void createFactorialTable();
	double Ni(int n, int i);
	double Bernstein(int n, int i, double t);

public:
	Bezier();
	std::vector<double> GenerateBezierCurve(std::vector<double> b, int cpts);
};
