#pragma once
#include"D3DHelper.h"
#include"GraphicHeader.h"
#include "VirtualObject.h"
#include<DirectXMath.h>
#include<DirectXColors.h>

using namespace DirectX;
class EngineRenderer :
	public VirtualObject
{
private:
	HWND WindowHandle;
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;
	IDXGISwapChain* SwapChain;
	GBuffer GeometryBuffer;
	ScreenInfo Info;

	D3D11_VIEWPORT MainViewport;

public:

private:
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnRelease() override;
public:



	void Clear(_In_ XMVECTORF32 ClearColor);

	EngineRenderer(_In_ UINT Width_, _In_ UINT Height_, _In_ HWND hWnd);
	EngineRenderer();
	virtual ~EngineRenderer();


};

