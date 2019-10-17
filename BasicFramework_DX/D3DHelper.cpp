#include "D3DHelper.h"


D3DHelper::D3DHelper()
{
}


D3DHelper::~D3DHelper()
{
}

bool D3DHelper::GeneratePrimitiveObjects(ID3D11Device *& Device, ID3D11DeviceContext*& Context)
{
	int Flags = 0;
	HRESULT Result = S_OK;

#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


	D3D_FEATURE_LEVEL Features[] = 
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_1
	};

	SUCCESS(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, Flags, Features, ARRAYSIZE(Features), D3D11_SDK_VERSION, &Device, nullptr, &Context));

	return true;
}

bool D3DHelper::GenerateSwapChain(IDXGISwapChain *& SwapChain, UINT Width, UINT Height, HWND hWnd, ID3D11Device *& Device)
{
	IDXGIFactory* Factory = nullptr;
	DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
	UINT Flags = 0;

#ifdef _DEBUG
	Flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	SwapChainDesc.BufferCount = 1;
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.Width = Width;
	SwapChainDesc.BufferDesc.Height = Height;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.Flags = Flags;
	SwapChainDesc.OutputWindow = hWnd;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SwapChainDesc.Windowed = true;

	SUCCESS(CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory));
 	SUCCESS(Factory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain));

	Factory->Release();

	return true;
}

bool D3DHelper::GenerateViewport(UINT Width, UINT Height, D3D11_VIEWPORT & OutViewport, _In_ ScreenInfo* Info)
{
	D3D11_VIEWPORT Temp;

	Temp.Width = Width;
	Temp.Height = Height;
	Temp.MinDepth = 0.0f;
	Temp.MaxDepth = 1.0f;
	Temp.TopLeftX = 0;
	Temp.TopLeftY = 0;

	OutViewport = Temp;

	Info->Context->RSSetViewports(1, &OutViewport);

	return true;
}

bool D3DHelper::GenerateSwapChainBuffer(ID3D11RenderTargetView *& RenderTartgetView, ScreenInfo* Info)
{
	ID3D11Texture2D* Texture = nullptr;

	SUCCESS(Info->SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&Texture));
	SUCCESS(Info->Device->CreateRenderTargetView(Texture, NULL, &RenderTartgetView));

	Info->Context->OMSetRenderTargets(1, &RenderTartgetView, Info->DepthStencilView);
	return true;
}

bool D3DHelper::SetRenderState(D3D11_FILL_MODE FillMode, ScreenInfo* Info)
{
	D3D11_RASTERIZER_DESC Desc{};

	ID3D11RasterizerState* RasterizerState;

	Desc.AntialiasedLineEnable = false;
	Desc.CullMode = D3D11_CULL_BACK;
	Desc.DepthBias = 0;
	Desc.DepthBiasClamp = 0;
	Desc.SlopeScaledDepthBias = 0;
	Desc.FillMode = FillMode;
	Desc.FrontCounterClockwise = false;
	Desc.ScissorEnable = false;
	Desc.MultisampleEnable = false;
	Desc.DepthClipEnable = false;

	SUCCESS(Info->Device->CreateRasterizerState(&Desc, &RasterizerState));
	
	return true;
}

bool D3DHelper::GenerateDepthStencilView(ID3D11DepthStencilView *& DepthStencilView, ScreenInfo * Info)
{
	ID3D11Texture2D* DepthStencil;
	D3D11_TEXTURE2D_DESC Desc{};
	D3D11_DEPTH_STENCIL_VIEW_DESC ViewDesc{};

	Desc.ArraySize = 1;
	Desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	Desc.CPUAccessFlags = 0;
	Desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	Desc.Height = Info->Height;
	Desc.Width = Info->Width;
	Desc.MipLevels = 1;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.Usage = D3D11_USAGE_DEFAULT;

	ViewDesc.Texture2D.MipSlice = 0;
	ViewDesc.Format = Desc.Format;
	ViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

	SUCCESS(Info->Device->CreateTexture2D(&Desc, nullptr, &DepthStencil));
	SUCCESS(Info->Device->CreateDepthStencilView(DepthStencil, &ViewDesc, &Info->DepthStencilView));

	return true;
}

bool D3DHelper::GenerateRenderTarget(ID3D11RenderTargetView*& RenderTargetView, D3D11_RENDER_TARGET_VIEW_DESC* Desc, ID3D11Texture2D* Texture, ID3D11Device* Device)
{
	SUCCESS(Device->CreateRenderTargetView(Texture, Desc, &RenderTargetView));

	return true;
}

BaseBuffer* D3DHelper::AllocConstantBuffer(ID3D11Device * Device, std::vector<Vertex>& Vertices, std::vector<UINT>& Indices)
{
	D3D11_BUFFER_DESC VBufferDesc{}, IBufferDesc{}, ABufferDesc{};

	D3D11_SUBRESOURCE_DATA VSubresource{}, ISubresource{};

	BaseBuffer* Buffer = new BaseBuffer();

	VBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	VBufferDesc.ByteWidth = sizeof(Vertex) * Vertices.size();
	VBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	IBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	IBufferDesc.ByteWidth = sizeof(UINT) * Indices.size();
	IBufferDesc.Usage = D3D11_USAGE_IMMUTABLE;

	ABufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ABufferDesc.ByteWidth = sizeof(ConstantBuffer);
	ABufferDesc.Usage = D3D11_USAGE_DEFAULT;

	VSubresource.pSysMem = Vertices.data();
	ISubresource.pSysMem = Indices.data();

	OUTSUCCESS(Device->CreateBuffer(&VBufferDesc, &VSubresource, &Buffer->VBuffer));
	OUTSUCCESS(Device->CreateBuffer(&IBufferDesc, &ISubresource, &Buffer->IBuffer));
	OUTSUCCESS(Device->CreateBuffer(&ABufferDesc, nullptr, &Buffer->ABuffer));


	return Buffer;
}

ID3D11InputLayout* D3DHelper::GenerateInputLayout(ID3D11Device * Device, LPCSTR Path)
{
	ID3D11InputLayout* InputLayout;

	ID3D11ShaderReflection* Reflect;
	D3D11_SHADER_DESC ShaderDesc{};

	ID3DBlob* VBlob, *ErrBlob;

	DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

	std::vector<D3D11_INPUT_ELEMENT_DESC> InputDesc;

	HRESULT Result;

#if defined _DEBUG
	ShaderFlags = D3DCOMPILE_DEBUG;
#endif

	SUCCESS(D3DX11CompileFromFileA(Path, nullptr, nullptr, "VS", "vs_5_0", ShaderFlags, NULL, nullptr, &VBlob, &ErrBlob, &Result));
	SUCCESS(D3DReflect(VBlob->GetBufferPointer(), VBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&Reflect));
	SUCCESS(Reflect->GetDesc(&ShaderDesc));

	for (WORD i = 0; i < ShaderDesc.InputParameters; i++)
	{
		static D3D11_SIGNATURE_PARAMETER_DESC ParamDesc;
		Reflect->GetInputParameterDesc(i, &ParamDesc);

		D3D11_INPUT_ELEMENT_DESC Element{};

		Element.SemanticName = ParamDesc.SemanticName;
		Element.SemanticIndex = ParamDesc.SemanticIndex;
		Element.InputSlot = 0;
		Element.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
		Element.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		Element.InstanceDataStepRate = 0;

		if(ParamDesc.Mask == 1)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				Element.Format = DXGI_FORMAT_R32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				Element.Format = DXGI_FORMAT_R32_FLOAT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				Element.Format = DXGI_FORMAT_R32_SINT;
		}
		else if (ParamDesc.Mask <= 3)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				Element.Format = DXGI_FORMAT_R32G32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				Element.Format = DXGI_FORMAT_R32G32_FLOAT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				Element.Format = DXGI_FORMAT_R32G32_SINT;
		}
		else if (ParamDesc.Mask <= 7)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				Element.Format = DXGI_FORMAT_R32G32B32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				Element.Format = DXGI_FORMAT_R32G32B32_FLOAT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				Element.Format = DXGI_FORMAT_R32G32B32_SINT;
		}
		else if (ParamDesc.Mask <= 15)
		{
			if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32)
				Element.Format = DXGI_FORMAT_R32G32B32A32_UINT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32)
				Element.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			else if (ParamDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32)
				Element.Format = DXGI_FORMAT_R32G32B32A32_SINT;
		}

		InputDesc.push_back(Element);

	}

	Reflect->Release();

	OUTSUCCESS(Device->CreateInputLayout(InputDesc.data(), InputDesc.size(), VBlob->GetBufferPointer(), VBlob->GetBufferSize(), &InputLayout));

	return InputLayout;
}

ID3DX11Effect* D3DHelper::GenerateEffect(ID3D11Device * Device, _In_ LPCSTR InPath)
{
	USES_CONVERSION;

	ID3DX11Effect* Effect;

	DWORD ShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
	HRESULT Result;

	ID3DBlob* ErrBlob = nullptr;

#if defined _DEBUG || defined DEBUG
	ShaderFlags = D3DCOMPILE_DEBUG;
#endif

	LPCWSTR Path = A2W(InPath);

	OUTSUCCESS(D3DX11CompileEffectFromFile(Path, nullptr, nullptr, ShaderFlags, 0, Device, &Effect, &ErrBlob));

	return Effect;
}

ID3D11ShaderResourceView* D3DHelper::GenerateTexture(ID3D11Device * Device, std::wstring Resource)
{
	ID3D11ShaderResourceView* SRV;
	std::wstring P = std::wstring(RELATIVE_ROOT) + Resource;
	HRESULT Result;

	D3DX11CreateShaderResourceViewFromFile(Device, P.c_str(), NULL, NULL, &SRV, &Result);

	OUTSUCCESS(Result);

	return SRV;
}

