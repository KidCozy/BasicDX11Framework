#pragma once


#include<d3d11.h>
#include<D3DX11.h>
#include<d3dcompiler.h>
#include<dxgi.h>
#include<DirectXMath.h>

#include<Windows.h>

/*d3d11.lib
d3dx11.lib
d3dcompiler.lib
dxgi.lib
Effects11d.lib*/
struct Vertex
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 UV;
	DirectX::XMFLOAT3 Normal;
	DirectX::XMFLOAT4 Color;
	//DirectX::XMFLOAT3 Tangent;
	//DirectX::XMFLOAT3 Binormal;
};

struct ConstantBuffer
{
	DirectX::XMMATRIX World;
	DirectX::XMMATRIX View;
	DirectX::XMMATRIX Projection;
};

struct BaseBuffer
{
	ID3D11Buffer* VBuffer = nullptr;
	ID3D11Buffer* IBuffer = nullptr;
	ID3D11Buffer* ABuffer = nullptr;
};

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
