#pragma once
#include "Shape.h"
#include "Material.h"

class Medium
{
public:
	Medium(Eigen::Vector3d _mediumCenterLocation, Shape* _mediumShape, Material* _meduimMaterial);

	Material* getMediumMaterial();

private:
	Eigen::Vector3d mediumCenterLocation;
	Shape* mediumShape;
	Material* meduimMaterial;
};

