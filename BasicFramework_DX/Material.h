#pragma once
#include"Transform.h"

#include<d3dx11effect.h>
#include<vector>

class DeviceSingle;
class Material
{
private:
	std::string Path;

	DeviceSingle* SingleInstance;

protected:

	ID3DX11Effect* Effect = nullptr;

	ID3DX11EffectMatrixVariable* World;
	ID3DX11EffectMatrixVariable* View;
	ID3DX11EffectMatrixVariable* Projection;

	D3DX11_PASS_DESC PassDesc;
	ID3D11InputLayout* InputLayout;
	

	std::vector<ID3DX11EffectTechnique*> Techniques;
	std::vector<ID3DX11EffectPass*> Passes;

	std::vector<ID3D11ShaderResourceView*> Textures;

public:

	LPCSTR GetShaderPath() const { return Path.c_str(); }

	ID3D11InputLayout*& GetInputLayoutPtr() { return InputLayout; }

	ID3DX11Effect*& GetEffectPtr() { return Effect; }

	void AddTexture(ID3D11ShaderResourceView* Texture) { Textures.push_back(Texture); }

	Material();
	Material(std::string Path_);
	
	~Material();
};

