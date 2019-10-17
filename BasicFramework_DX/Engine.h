#pragma once

#include"EngineRenderer.h"
#include "VirtualObject.h"
class Engine : public VirtualObject
{
private:
	HWND WindowHandle;

	UINT WIDTH = 800;
	UINT HEIGHT = 600;

	EngineRenderer Renderer;

public:
	Engine() {}
	Engine(HWND hWnd);
	virtual ~Engine();

	_inline void Resize(UINT NewWidth, UINT NewHeight) { WIDTH = NewWidth; HEIGHT = NewHeight; Renderer.Resize(WIDTH, HEIGHT); }


private:
	// VirtualObject을(를) 통해 상속됨
	virtual void OnInit() override;
	virtual void OnUpdate() override;
	virtual void OnRender() override;
	virtual void OnRelease() override;

};

