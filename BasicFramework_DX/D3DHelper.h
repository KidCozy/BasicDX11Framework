#pragma once

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include"Utility.h"
#include<d3d11.h>
#include<d3dcompiler.h>
#include<dxgi.h>

class D3DHelper
{
public:
	D3DHelper();
	~D3DHelper();

	static bool GeneratePrimitiveObjects(_Out_ ID3D11Device*& Device, _Out_ ID3D11DeviceContext*& Context);
	static bool GenerateSwapChain(_Out_ IDXGISwapChain*& SwapChain, UINT Width, UINT Height, HWND hWnd, ID3D11Device *& Device);
	static bool GenerateViewport(_In_ UINT Width, _In_ UINT Height, _Out_ D3D11_VIEWPORT& OutViewport, _In_ ScreenInfo* Info);

	static bool GenerateSwapChainBuffer(_Out_ ID3D11RenderTargetView*& RenderTartgetView, ScreenInfo* Info);
	static bool SetRenderState(_Out_ D3D11_FILL_MODE FillMode, ScreenInfo* Info);

	static bool GenerateDepthStencilView(_Out_ ID3D11DepthStencilView*& DepthStencilView, _In_ ScreenInfo* Info);

};

