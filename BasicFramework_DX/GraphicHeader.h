#pragma once
#include<D3D11.h>

struct GBuffer
{
	ID3D11Texture2D* Texture = nullptr;
	ID3D11RenderTargetView* RenderTargetView = nullptr;
	ID3D11ShaderResourceView* ShaderResourceView = nullptr;
};

struct ScreenInfo
{
	UINT Width;
	UINT Height;

	IDXGISwapChain* SwapChain;
	ID3D11Device* Device;
	ID3D11DeviceContext* Context;

	ID3D11RenderTargetView* MergeView = nullptr;
	ID3D11DepthStencilView* DepthStencilView = nullptr;
	GBuffer* GBufferPtr;

	D3D11_VIEWPORT MainViewport;

	ScreenInfo() {}
	ScreenInfo(UINT Width_, UINT Height_, IDXGISwapChain* SwapChain_, ID3D11Device* Device_, ID3D11DeviceContext* Context_, GBuffer* GBuffer_) :
		Width(Width_), Height(Height_), SwapChain(SwapChain_), Device(Device_), Context(Context_), GBufferPtr(GBuffer_) {}
};