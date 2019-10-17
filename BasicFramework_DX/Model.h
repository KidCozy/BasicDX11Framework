#pragma once
#pragma warning(disable:4996)

#include"Material.h"
#include"GraphicHeader.h"


using namespace std;
using namespace DirectX;

class Model : public Material
{
private:
	std::FILE*  File;
	std::string Path;
protected:
	std::vector<Vertex> Vertices;
	std::vector<UINT> Indices;

	Matrix4x4 MeshTransform;
	BaseBuffer BBuffer;
	ConstantBuffer CBuffer;

protected:
	const std::FILE* GetFile() const { return File; }


public: 
	void Read();


	UINT VertexCount() const { return Vertices.size(); }
	UINT IndexCount() const { return Indices.size(); }

	Vertex* GetVertices() { return Vertices.data(); }
	UINT* GetIndices() { return Indices.data(); }

	BaseBuffer* OutBaseBuffer() { return &BBuffer; }
	ConstantBuffer* OutConstantBuffer() { return &CBuffer; }
	XMFLOAT4X4* GetTransform() { return &MeshTransform.GetTransform(); }

	void SetWorldMatrix(XMMATRIX* Mat) { World->SetMatrix((float*)&Mat); }
	void SetViewMatrix(XMMATRIX* Mat) { View->SetMatrix((float*)&Mat); }
	void SetProjectionMatrix(XMMATRIX* Mat) { Projection->SetMatrix((float*)&Mat); }

	std::string GetMeshFileName() const { return Path; }

private:


public:
	Model() {
	
	//	this = new Model("Default");
	
	}
	Model(std::string Path);
	virtual ~Model();
};

