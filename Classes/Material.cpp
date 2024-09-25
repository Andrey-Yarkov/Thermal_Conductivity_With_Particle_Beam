#include "Material.h"

Material::Material(std::string _materialName)
{
	materialName = _materialName;

	if (_materialName == "Glass" || _materialName == "SiO2")
	{
		density = 2.5 * phys::g() / pow(phys::cm(), 3.0);
		conductivity = 0.8 * phys::J() / phys::s() / phys::m() / phys::K();
		capacity = 703 * phys::J() / phys::K() / phys::kg();
	}
}

double Material::getDensity()
{
	return density;
}

double Material::getConductivity()
{
	return conductivity;
}

double Material::getCapacity()
{
	return capacity;
}

void Material::loadAbsorbedEnergyPerProtonData(std::string fileLocation)
{
	std::ifstream inFile;
	inFile.open(fileLocation);

	double depth;
	double depthUnits = phys::um();
	double energyDens;
	double energyDensUnits = phys::KeV() / phys::um();
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile >> depth >> energyDens;
			depthsProton.push_back(depth * depthUnits);
			energyDensPerProton.push_back(energyDens * energyDensUnits);
		}
		inFile.close();

		std::cout << "Файл Protons успешно прочитан" << std::endl;
	}
	else
	{
		std::cout << "Ошибка при прочтении файла Protons" << std::endl;
	}
}

void Material::loadAbsorbedEnergyPerElectronData(std::string fileLocation)
{
	std::ifstream inFile;
	inFile.open(fileLocation);

	double depth;
	double depthUnits = phys::g() / pow(phys::cm(), 2.0);
	double energyDens;
	double energyDensUnits = phys::MeV() * (phys::g() / pow(phys::cm(), 2.0));
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile >> depth >> energyDens;
			depthsElectron.push_back(depth * depthUnits / density);
			energyDensPerElectron.push_back(energyDens * energyDensUnits * density);
		}
		inFile.close();

		std::cout << "Файл Electrons успешно прочитан" << std::endl;
	}
	else
	{
		std::cout << "Ошибка при прочтении файла Electrons" << std::endl;
	}
}

double Material::getAbsorbedEnergyDensPerProton(double depth)
{
	int index = 0;
	for (double depthProton : depthsProton)
	{
		if (depth > depthProton)
		{
			index++;
			continue;
		}
		else
		{
			break;
		}
	}

	if (index >= depthsProton.size())
	{
		return 0.0;
	}
	else
	{
		return energyDensPerProton.at(index);
	}
}

double Material::getAbsorbedEnergyDensPerElectron(double depth)
{
	int index = 0;
	for (double depthElectron : depthsElectron)
	{
		if (depth > depthElectron)
		{
			index++;
			continue;
		}
		else
		{
			break;
		}
	}

	if (index >= depthsElectron.size())
	{
		return 0.0;
	}
	else
	{
		return energyDensPerElectron.at(index);
	}
}