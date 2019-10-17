#include "Material.h"
#include"D3DHelper.h"
#include"DeviceSingle.h"

Material::Material()
{
	USES_CONVERSION;

	std::wstring root = std::wstring(RELATIVE_ROOT);
	std::wstring file = std::wstring(L"DefaultShader.fx");

	root += file;
	Path = W2A(root.c_str());

	SingleInstance = DeviceSingle::GetInstance();

	D3DHelper::GenerateEffect(SingleInstance->Device, Path.c_str());

	if (Effect != nullptr)
	{
		World = Effect->GetVariableByName("World")->AsMatrix();
		View = Effect->GetVariableByName("View")->AsMatrix();
		Projection = Effect->GetVariableByName("Projection")->AsMatrix();
	}
}


Material::Material(std::string Path_)
{

}


Material::~Material()
{
}
