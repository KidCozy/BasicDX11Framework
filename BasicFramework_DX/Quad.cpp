#include "Quad.h"



Quad::Quad()
{
	Vertex vertices[4] = {
		{ { -1.0f, -1.0f, 0.0f }, { 0.0f, 1.0f } },
		{ { 1.0f, -1.0f, 0.0f }, { 1.0f, 1.0f } },
		{ { -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f } },
		{ { 1.0f, 1.0f, 0.0f }, { 1.0f, 0.0f } }
	};

	UINT i[6] = { 0, 1, 2, 1, 2, 3 };

	Vertices.push_back(vertices[0]);
	Vertices.push_back(vertices[1]);
	Vertices.push_back(vertices[2]);
	Vertices.push_back(vertices[3]);

	Indices.push_back(i[0]);
	Indices.push_back(i[1]);
	Indices.push_back(i[2]);
	Indices.push_back(i[3]);
	Indices.push_back(i[4]);
	Indices.push_back(i[5]);

	Texture = Effect->GetVariableByName("ScreenTexture")->AsShaderResource();
}


Quad::~Quad()
{
}
