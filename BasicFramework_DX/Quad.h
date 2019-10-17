#pragma once
#include"Model.h"
class Quad : public Model
{
private:
	ID3DX11EffectShaderResourceVariable* Texture;
public:
	Quad();
	virtual ~Quad();
};

