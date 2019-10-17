#pragma once
#include"Transform.h"
class Entity
{
public:
	Matrix4x4 Transform;
	
public:

	void operator=(XMFLOAT4X4 Mat);

	XMMATRIX* GetTransform() { return &XMLoadFloat4x4(&Transform.GetTransform()); }

	Entity();
	~Entity();
};

