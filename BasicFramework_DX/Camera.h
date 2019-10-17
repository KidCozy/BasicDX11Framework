#pragma once
#include"Entity.h"
#include"VirtualObject.h"

class Camera : public VirtualObject, public Entity
{
private:

	float FOV;
	float Near;
	float Far;
	float AspectRatio;

	Matrix4x4 Projection;

public:
	XMMATRIX* GetView() { return GetTransform(); }
	XMMATRIX* GetProjection() { return &XMLoadFloat4x4(&Projection.GetTransform()); }

private:
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnRelease() override;

public:
	Camera();
	Camera(float FOV_, float Near_, float Far_, float AspectRatio_);
	~Camera();

};

