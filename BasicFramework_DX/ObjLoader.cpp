#include "stdafx.h"
#include "ObjLoader.h"


Model* ObjLoader::Load(std::string Path)
{
	Model* NewModel = new Model(Path);
	NewModel->Read();
	return NewModel;
}

ObjLoader::ObjLoader()
{
}


ObjLoader::~ObjLoader()
{
}
