#include "stdafx.h"
#include "Model.h"


void Model::Read()
{
	int Res = 0;
	std::vector<XMFLOAT3> TempVertices;
	std::vector<XMFLOAT2> TempUV;
	std::vector<XMFLOAT3> TempNormals;
	std::vector<UINT> ViVector, UiVector, NiVector;
	Vertex v;

	do {
		char Header[1024] = "";
		XMFLOAT3 Temp_vertex = XMFLOAT3();
		XMFLOAT2 Temp_uv = XMFLOAT2();
		XMFLOAT3 Temp_normal = XMFLOAT3();
		UINT vi[3], ui[3], ni[3];

		Res = fscanf(File, "%s", Header);

		if (strcmp(Header, "v") == 0)
		{

			fscanf(File, "%f %f %f\n", &Temp_vertex.x, &Temp_vertex.y, &Temp_vertex.z);
			TempVertices.push_back(Temp_vertex);

		}
		else if (strcmp(Header, "vt") == 0)
		{
			fscanf(File, "%f %f\n", &Temp_uv.x, &Temp_uv.y);
			TempUV.push_back(Temp_uv);
		}
		else if (strcmp(Header, "vn") == 0)
		{

			fscanf(File, "%f %f %f\n", &Temp_normal.x, &Temp_normal.y, &Temp_normal.z);
			TempNormals.push_back(Temp_normal);
		}
		else if (strcmp(Header, "f") == 0)
		{
			int Matches = fscanf(File, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vi[0], &ui[0], &ni[0], &vi[1], &ui[1],&ni[1], &vi[2], &ui[2], &ni[2]);
			if (Matches != 9)
			{
				std::cout << "The file can't be read via this program." << std::endl;
				return;
			}

			ViVector.push_back(vi[0]);
			ViVector.push_back(vi[1]);
			ViVector.push_back(vi[2]);
			
			UiVector.push_back(ui[0]);
			UiVector.push_back(ui[1]);
			UiVector.push_back(ui[2]);

			NiVector.push_back(ni[0]);
			NiVector.push_back(ni[1]);
			NiVector.push_back(ni[2]);

		}



	} while (Res != EOF);

	std::cout << std::endl;

	for (UINT i = 0; i < ViVector.size(); i++)
	{
		UINT VIndex = ViVector[i];
		v.Position = TempVertices[VIndex - 1];
		Vertices.push_back(v);
	}

	for (UINT i = 0; i < UiVector.size(); i++)
	{
		UINT UIndex = UiVector[i];
		v.UV = TempUV[UIndex - 1];
	}

	for (UINT i = 0; i < NiVector.size(); i++)
	{
		UINT NIndex = NiVector[i];
		v.Normal = TempNormals[NIndex - 1];
	}

	Indices = ViVector;

	fclose(File);

}

Model::Model(std::string ModelPath)
{
	Path = ModelPath;
	File =fopen(ModelPath.c_str(), "r");
	if (File == nullptr)
	{
		std::cout << "This file is not available : " << ModelPath.c_str() <<std::endl;
		return;
	}

}


Model::~Model()
{
}
