#pragma once
#include<DirectXMath.h>
#include<iostream>

using namespace DirectX;

struct MatrixPtr 
{
	float* _11, *_12, *_13, *_14;
	float* _21, *_22, *_23, *_24;
	float* _31, *_32, *_33, *_34;
	float* _41, *_42, *_43, *_44;

	bool SetMatrixPointer(XMFLOAT4X4* Matrix);
};

struct VectorPtr
{
	float* x, *y, *z, *w;

	bool SetVectorPointer(float* Element1, float* Element2, float* Element3, float* Element4);
};

struct Matrix4x4
{
private:
	XMFLOAT4X4 Origin;
	MatrixPtr Matrix;

	VectorPtr Position;
	VectorPtr Rotation;
	VectorPtr Scale;

private:
	MatrixPtr* GetMatrixPointer() { return &Matrix; }

public:
	void Translation(XMVECTOR Offset);
	void Rotate(XMVECTOR Offset);
	void SetScale(XMVECTOR NewScale);

	_inline void SetMatrix(XMMATRIX Mat) { XMStoreFloat4x4(&Origin, Mat); }
	_inline void operator=(XMMATRIX Mat) { XMStoreFloat4x4(&Origin, Mat); }


	XMFLOAT4X4 GetTransform() const { return Origin; }
	XMFLOAT3 GetPosition() const { return XMFLOAT3(Origin._41, Origin._42, Origin._43); }
	XMFLOAT3 GetRotation() const { return XMFLOAT3(Origin._11, Origin._22, Origin._33); }
	XMFLOAT3 GetScale() const;

	Matrix4x4();
	~Matrix4x4();

};

