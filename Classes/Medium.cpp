#include "Medium.h"

Medium::Medium(Eigen::Vector3d _mediumCenterLocation, Shape* _mediumShape, Material* _meduimMaterial)
{
	mediumCenterLocation = _mediumCenterLocation;
	mediumShape = _mediumShape;
	meduimMaterial = _meduimMaterial;
}

Material* Medium::getMediumMaterial()
{
	return meduimMaterial;
}