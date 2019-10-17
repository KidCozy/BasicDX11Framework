#pragma once
#include"Camera.h"
#include"ObjLoader.h"

#include "VirtualObject.h"


#include<DirectXMath.h>
#include<DirectXColors.h>



using namespace DirectX;

class DeviceSingle;
class EngineRenderer :
	public VirtualObject
{
private:
	DeviceSingle* Instance_;
	HWND WindowHandle;
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;
	IDXGISwapChain* SwapChain = nullptr;
	GBuffer GeometryBuffer;
	ScreenInfo Info;

	D3D11_VIEWPORT MainViewport;
	
	Camera* MainCamera = new Camera(XM_1DIV2PI, 0.01f, 100.0f, 1.333f);
	

public:
	Model* Mesh1 = new Model();


private:
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnRelease() override;
public:



	void Clear(_In_ XMVECTORF32 ClearColor);
	void Resize(_In_ UINT Width, _In_ UINT Height);

	void RenderMesh(_In_ Model* Mesh);
	void BindBuffer(_In_ Model* Mesh);

	void SetMainCamera(_In_ Camera* MainCamera_) { MainCamera = MainCamera_; }

	EngineRenderer(_In_ UINT Width_, _In_ UINT Height_, _In_ HWND hWnd);
	EngineRenderer();
	virtual ~EngineRenderer();


};

