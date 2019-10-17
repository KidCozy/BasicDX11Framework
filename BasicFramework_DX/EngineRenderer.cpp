#include "stdafx.h"
#include "EngineRenderer.h"
#include"D3DHelper.h"
#include"DeviceSingle.h"

void EngineRenderer::Clear(_In_ XMVECTORF32 ClearColor)
{
	Info.Context->ClearRenderTargetView(Info.MergeView, ClearColor);
	Info.Context->ClearDepthStencilView(Info.DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void EngineRenderer::Resize(UINT Width, UINT Height)
{
	if (SwapChain == nullptr)
		return;
	ID3D11Texture2D* NewBuffer;

	Info.Width = Width;
	Info.Height = Height;

	SwapChain->ResizeBuffers(1, Width, Height, DXGI_FORMAT_R8G8B8A8_UNORM, 0);

	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&NewBuffer);

	D3DHelper::GenerateRenderTarget(Info.MergeView, nullptr, NewBuffer, Device);



}

void EngineRenderer::RenderMesh(_In_ Model * Mesh)
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;

	Mesh->SetWorldMatrix(&XMLoadFloat4x4(Mesh->GetTransform()));
	Mesh->SetViewMatrix(MainCamera->GetTransform());
	Mesh->SetProjectionMatrix(MainCamera->GetProjection());

	BindBuffer(Mesh);

	Context->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Context->IASetInputLayout(Mesh->GetInputLayoutPtr());
	Context->DrawIndexed(Mesh->IndexCount(), 0, 0);
}

void EngineRenderer::BindBuffer(_In_ Model * Mesh)
{
	static const UINT Stride = sizeof(Vertex);
	static const UINT Offset = 0;

	Context->IASetVertexBuffers(0, 1, &Mesh->OutBaseBuffer()->VBuffer, &Stride, &Offset);
	Context->IASetIndexBuffer(Mesh->OutBaseBuffer()->IBuffer, DXGI_FORMAT_R32_UINT, 0);
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
	Instance_ = DeviceSingle::GetInstance();
	Instance_->Device = Device;

	D3DHelper::GenerateSwapChainBuffer(Info.MergeView, &Info);
	D3DHelper::GenerateDepthStencilView(Info.DepthStencilView, &Info);
	D3DHelper::GenerateViewport(Info.Width, Info.Height, MainViewport, &Info);

	std::cout << Mesh1->GetMeshFileName() << std::endl;

	Mesh1 = ObjLoader::Load("Models\\Cube.obj");
	//D3DHelper::GenerateEffect(Device, Mesh1);
	//D3DHelper::AllocConstantBuffer(Device, Mesh1);

}

void EngineRenderer::OnUpdate()
{
	Clear(Colors::Black);

	RenderMesh(Mesh1);

}

void EngineRenderer::OnRender()
{
	Info.SwapChain->Present(0, 0);
}

void EngineRenderer::OnRelease()
{
}
