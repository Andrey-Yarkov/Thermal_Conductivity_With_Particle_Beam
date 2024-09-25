#pragma once
#include <vector>

#include "Medium.h"

class NonStatThermalCondEq
{
public:
	NonStatThermalCondEq(std::vector<double> _spatialNodalGrid, std::vector<double> _timeNodalGrid, std::vector<double> _initCond,
		std::string _boundCondType, std::vector<double> _leftBoundCond, std::vector<double> _rightBoundCond, Medium* _medium, std::vector<std::vector<double>> _sourceTerm);

	void recordSolution(std::string filePath);

private:
	void sweepMethodDR(); // Dirichlet - Radiation flux

	double parameter;
	std::vector<double> spatialNodalGrid;
	std::vector<double> timeNodalGrid;
	std::vector<double> initCond;
	std::vector<double> boundCond;
	std::vector<double> leftBoundCond;
	std::vector<double> rightBoundCond;
	std::string boundCondType;
	std::vector<std::vector<double>> sourceTerm;
	Medium* medium;

	double spatialStep;
	double timeStep;
	int M;
	int N;
	std::vector<double> coefficientsA;
	std::vector<double> coefficientsB;
	std::vector<std::vector<double>> solution;
};