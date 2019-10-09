#include "stdafx.h"
#include "EngineRenderer.h"


void EngineRenderer::Clear(_In_ XMVECTORF32 ClearColor)
{
	Info.Context->ClearRenderTargetView(Info.MergeView, ClearColor);
	Info.Context->ClearDepthStencilView(Info.DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

EngineRenderer::EngineRenderer(_In_ UINT Width_, _In_ UINT Height_, _In_ HWND hWnd)
{
	Info.Width = Width_;
	Info.Height = Height_;
	WindowHandle = hWnd;
}

EngineRenderer::EngineRenderer()
{
}


EngineRenderer::~EngineRenderer()
{
}

void EngineRenderer::OnInit()
{
	D3DHelper::GeneratePrimitiveObjects(Device, Context);
	D3DHelper::GenerateSwapChain(SwapChain, Info.Width, Info.Height, WindowHandle, Device);


	Info = ScreenInfo(Info.Width, Info.Height, SwapChain, Device, Context, &GeometryBuffer);

	D3DHelper::GenerateSwapChainBuffer(Info.MergeView, &Info);
	D3DHelper::GenerateDepthStencilView(Info.DepthStencilView, &Info);
	D3DHelper::GenerateViewport(Info.Width, Info.Height, MainViewport, &Info);

}

void EngineRenderer::OnUpdate()
{
	Clear(Colors::Black);
}

void EngineRenderer::OnRender()
{
	Info.SwapChain->Present(0, 0);
}

void EngineRenderer::OnRelease()
{
}
