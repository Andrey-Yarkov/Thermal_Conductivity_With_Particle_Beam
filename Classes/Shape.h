#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "Eigen/Eigen"

class Shape
{
public:
	Shape();

	virtual Eigen::VectorXd getProportions() = 0;

protected:
	int dimensions;
};


class Parallelepiped : public Shape
{
public:
	Parallelepiped(double _a, double _b, double _c);

	Eigen::VectorXd getProportions();

private:
	double a, b, c;
};