#pragma once
#include"D3DHelper.h"
#include"EngineRenderer.h"
#include "VirtualObject.h"

#define WIDTH 800
#define HEIGHT 600

class Engine : public VirtualObject
{
private:
	HWND WindowHandle;


	EngineRenderer Renderer;

public:
	Engine() {}
	Engine(HWND hWnd);
	virtual ~Engine();

private:
	// VirtualObject을(를) 통해 상속됨
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnRelease() override;

};

