#include "Shape.h"

Shape::Shape()
{
}


Parallelepiped::Parallelepiped(double _a, double _b, double _c)
{
	dimensions = 3;
	a = _a;
	b = _b;
	c = _c;
}

Eigen::VectorXd Parallelepiped::getProportions()
{
	Eigen::VectorXd proportions(dimensions);
	proportions << a, b, c;

	return proportions;
}