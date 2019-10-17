#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(float FOV_, float Near_, float Far_, float AspectRatio_)
{
	FOV = FOV_;
	Near = Near_;
	Far = Far_;
	AspectRatio = AspectRatio_;

	Transform = XMMatrixLookAtLH(XMVectorSet(1.0f, 0.0f, 1.0f, 1.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));
	Projection = XMMatrixPerspectiveFovLH(FOV, AspectRatio, Near, Far); 
}


Camera::~Camera()
{
}

void Camera::OnInit()
{
}

void Camera::OnUpdate()
{
}

void Camera::OnRender()
{
}

void Camera::OnRelease()
{
}
