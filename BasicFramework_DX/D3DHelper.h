#pragma once

#include<d3dx11effect.h>

#include"Utility.h"
#include"GraphicHeader.h"

#define DEFAULT_MATERIAL "DefaultShader.hlsl"
#define RELATIVE_ROOT L"C:\\Users\\pencu\\Desktop\\Personal\\Projects\\RayMarching\\BasicFramework_DX\\"

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
	static bool GenerateRenderTarget(_Out_ ID3D11RenderTargetView*& RenderTargetView, D3D11_RENDER_TARGET_VIEW_DESC* Desc, _In_ ID3D11Texture2D* Texture, ID3D11Device* Device);

	static BaseBuffer* AllocConstantBuffer(_In_ ID3D11Device* Device, std::vector<Vertex>& Vertices, std::vector<UINT>& Indices);

	static ID3D11InputLayout* GenerateInputLayout(_In_ ID3D11Device* Device, LPCSTR Path);
	static ID3DX11Effect* GenerateEffect(_In_ ID3D11Device* Device, _In_ LPCSTR InPath);
	static ID3D11ShaderResourceView* GenerateTexture(_In_ ID3D11Device* Device, std::wstring Resource);

};

