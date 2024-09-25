#include "NonStatThermalCondEq.h"

NonStatThermalCondEq::NonStatThermalCondEq(std::vector<double> _spatialNodalGrid, std::vector<double> _timeNodalGrid, std::vector<double> _initCond,
	std::string _boundCondType, std::vector<double> _leftBoundCond, std::vector<double> _rightBoundCond, Medium* _medium, std::vector<std::vector<double>> _sourceTerm)
{
	spatialNodalGrid = _spatialNodalGrid;
	timeNodalGrid = _timeNodalGrid;
	initCond = _initCond;
	boundCondType = _boundCondType;
	leftBoundCond = _leftBoundCond;
	rightBoundCond = _rightBoundCond;
	medium = _medium;

	std::vector<double> sourceTermAtT;
	for (std::vector<double> sourceT : _sourceTerm)
	{
		sourceTermAtT.clear();
		for (double sourceX : sourceT)
		{
			sourceTermAtT.push_back(sourceX / (_medium->getMediumMaterial()->getDensity() * _medium->getMediumMaterial()->getCapacity()));
		}
		sourceTerm.push_back(sourceTermAtT);
	}

	parameter = pow(_medium->getMediumMaterial()->getConductivity() / (_medium->getMediumMaterial()->getDensity() * _medium->getMediumMaterial()->getCapacity()), 0.5);
	spatialStep = _spatialNodalGrid.at(1) - _spatialNodalGrid.at(0);
	timeStep = _timeNodalGrid.at(1) - _timeNodalGrid.at(0);
	M = _spatialNodalGrid.size() - 1;
	N = _timeNodalGrid.size() - 1;

	solution.push_back(initCond);

	if (_boundCondType == "Dirichlet_Radiation")
	{
		sweepMethodDR();
	}
}

void NonStatThermalCondEq::sweepMethodDR()
{
	std::vector<double> solutionAtTimeStep;
	double solutionAtPoint;
	std::vector<double> coefficientsA;
	std::vector<double> coefficientsB;
	std::vector<double> reverseSolutionAtTimeStep;

	double factor = pow(parameter / spatialStep, 2.0) * timeStep;

	double A = 1.0;
	double B = 1.0;
	double C = 2.0 + 1.0 / factor;
	double FFactorSol = 1 / factor;
	double FFactorSource = spatialStep * spatialStep / parameter / parameter;
	double radiationCoef;

	for (int n = 1; n <= N; n++)
	{
		coefficientsA.clear();
		coefficientsB.clear();

		coefficientsA.push_back(0.0);
		coefficientsB.push_back(leftBoundCond.at(n));
		for (int m = 2; m <= M; m++)
		{
			coefficientsA.push_back(B / (C - A * coefficientsA.at(m - 2)));
			coefficientsB.push_back((A * coefficientsB.at(m - 2) + FFactorSol * solution.at(n - 1).at(m - 1) + 
				FFactorSource * sourceTerm.at(n - 1).at(m - 1)) / (C - A * coefficientsA.at(m - 2)));
		}

		radiationCoef = phys::stefanBoltzmanConstant() * spatialStep / medium->getMediumMaterial()->getConductivity() * pow(solution.at(n - 1).at(M), 3.0);

		solutionAtTimeStep.clear();
		reverseSolutionAtTimeStep.clear();
		reverseSolutionAtTimeStep.push_back((coefficientsB.at(M - 1) + (solution.at(n - 1).at(M) + timeStep * sourceTerm.at(n).at(M)) / factor / 2.0 ) /
			(1.0 + 0.5 / factor - coefficientsA.at(M - 1) + radiationCoef));
		int reverseIndex = 0;
		for (int m = M - 1; m >= 0; m--)
		{
			reverseSolutionAtTimeStep.push_back(coefficientsA.at(m) * reverseSolutionAtTimeStep.at(reverseIndex) + coefficientsB.at(m));
			reverseIndex++;
		}

		solutionAtTimeStep = reverseSolutionAtTimeStep;
		std::reverse(solutionAtTimeStep.begin(), solutionAtTimeStep.end());

		solution.push_back(solutionAtTimeStep);
	}
}

void NonStatThermalCondEq::recordSolution(std::string filePath)
{
	std::string fileName;

	for (int n = 0; n < timeNodalGrid.size(); n++)
	{
		fileName = std::to_string(timeNodalGrid.at(n)) + ".mat";

		std::ofstream outFile;
		outFile.open(filePath + fileName);
		for (int m = 0; m < spatialNodalGrid.size(); m++)
		{
			outFile << spatialNodalGrid.at(m) << "\t" << solution.at(n).at(m) << "\n";
		}
		outFile.close();

		std::cout << "Файл " + fileName + " успешно создан" << std::endl;
	}
}