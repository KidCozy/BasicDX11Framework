#pragma once
#include"Model.h"

class ObjLoader
{
public:
	
	static Model* Load(std::string Path);

	ObjLoader();
	~ObjLoader();
};

