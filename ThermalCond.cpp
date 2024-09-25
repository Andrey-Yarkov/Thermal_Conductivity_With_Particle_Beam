#include <iostream>
#include <string>
#include <direct.h>

#include "Eigen/Eigen"
#include "Namespaces\Phys.h"
#include "Classes\Shape.h"
#include "Classes\Material.h"
#include "Classes\Medium.h"
#include "Classes\NonStatThermalCondEq.h"

void nonStationaryTemperatureDistrib();


int main()
{
	setlocale(LC_ALL, "Russian"); // Отображение кириллицы в консоли
	std::cout.precision(6); // Точность вывода десятичных чисел
	std::srand(time(0)); // Синхронизация рандомайзера с текущем временем

	nonStationaryTemperatureDistrib();
}


void nonStationaryTemperatureDistrib()
{
	double duration = 200.0 * phys::ms();
	double mediumLength = 40.0 * phys::mm();
	double mediumWidth = 40.0 * phys::mm();
	double mediumHeight = 0.17 * phys::mm();

	Eigen::Vector3d mediumCenterLocation = Eigen::Vector3d(0.0, 0.0, mediumHeight / 2.0);

	double tableTemperature = (20.0 + 273.15) * phys::K();
	double protonEnergy = 30.0 * phys::KeV();
	double electronEnergy = 15.0 * phys::KeV();
	double protonFlowDensity = 0.0 / phys::s() / pow(phys::cm(), 2.0); // 0.0, 1e9, 1e10, 1e11, 1e12
	double electronFlowDensity = 1e13 / phys::s() / pow(phys::cm(), 2.0); // 0.0, 1e10, 1e11, 1e12, 1e13

	std::string inputDataFolder = "D:/Основные файлы/Учёба/Вуз/Вычислительная физика/8 семестр/Курсовая/ThermalCond/InputData/";

	Shape* mediumShape = new Parallelepiped(mediumLength, mediumWidth, mediumHeight);
	Material* mediumMaterial = new Material("Glass");
	mediumMaterial->loadAbsorbedEnergyPerProtonData(inputDataFolder + "AbsEnDensPerProton.txt");
	mediumMaterial->loadAbsorbedEnergyPerElectronData(inputDataFolder + "AbsEnDensPerElectron.txt");
	Medium* medium = new Medium(mediumCenterLocation, mediumShape, mediumMaterial);

	std::vector<double> initCond;
	std::string boundCondType = "Dirichlet_Radiation";
	std::vector<double> leftBoundCond;
	std::vector<double> rightBoundCond;
	std::vector<std::vector<double>> sourceTerm;

	int numberOfSpatialNodes = 100;
	std::vector<double> spatialNodalGrid;
	for (int m = 0; m < numberOfSpatialNodes; m++)
	{
		spatialNodalGrid.push_back(0.0 + m * mediumHeight / (numberOfSpatialNodes - 1.0));
		initCond.push_back(tableTemperature);
	}

	int numberOfTimeNodes = 1000;
	std::vector<double> timeNodalGrid;
	std::vector<double> sourceTermAtT;
	for (int n = 0; n < numberOfTimeNodes; n++)
	{
		timeNodalGrid.push_back(0.0 + n * duration / (numberOfTimeNodes - 1.0));
		leftBoundCond.push_back(tableTemperature);
		rightBoundCond.push_back(tableTemperature);

		sourceTermAtT.clear();
		for (int m = 0; m < numberOfSpatialNodes; m++)
		{
			sourceTermAtT.push_back(mediumMaterial->getAbsorbedEnergyDensPerProton(spatialNodalGrid.at(m)) * protonFlowDensity +
				mediumMaterial->getAbsorbedEnergyDensPerElectron(spatialNodalGrid.at(m)) * electronFlowDensity);
		}
		std::reverse(sourceTermAtT.begin(), sourceTermAtT.end());

		sourceTerm.push_back(sourceTermAtT);
	}

	std::string outputDataFolder = "D:/Основные файлы/Учёба/Вуз/Вычислительная физика/8 семестр/Курсовая/ThermalCond/OutputData/";
	std::string sourceFolder = "0_1e13/";
	bool outputDataFolderCreated = _mkdir(outputDataFolder.c_str());
	bool sourceFolderCreated = _mkdir((outputDataFolder + sourceFolder).c_str());

	NonStatThermalCondEq* diffEq = new NonStatThermalCondEq(spatialNodalGrid, timeNodalGrid, initCond, boundCondType, leftBoundCond, rightBoundCond, medium, sourceTerm);
	diffEq->recordSolution(outputDataFolder + sourceFolder);
}