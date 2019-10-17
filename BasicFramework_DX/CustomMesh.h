#pragma once
#include "Model.h"
class CustomMesh :
	public Model
{
private:
	std::string Name;
public:
	CustomMesh();
	virtual ~CustomMesh();
};

