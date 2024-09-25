#pragma once
#include <iostream>
#include <string>
#include <math.h>
#include <vector>
#include <fstream>

#include "Phys.h"

class Material
{
public:
	Material(std::string _materialName);

	double getDensity();
	double getConductivity();
	double getCapacity();

	void loadAbsorbedEnergyPerProtonData(std::string fileLocation);
	void loadAbsorbedEnergyPerElectronData(std::string fileLocation);

	double getAbsorbedEnergyDensPerProton(double depth);
	double getAbsorbedEnergyDensPerElectron(double depth);

private:
	std::string materialName;
	double density;
	double conductivity;
	double capacity;
	std::vector<double> depthsProton;
	std::vector<double> energyDensPerProton;
	std::vector<double> depthsElectron;
	std::vector<double> energyDensPerElectron;
};