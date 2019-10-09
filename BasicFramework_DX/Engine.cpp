#include "stdafx.h"
#include "Engine.h"


Engine::Engine(HWND hWnd)
{

	WindowHandle = hWnd;
	AllocConsole();
}


Engine::~Engine()
{
}

void Engine::OnInit()
{
	Renderer = EngineRenderer(WIDTH, HEIGHT, WindowHandle);

	Renderer.Init();
}

void Engine::OnUpdate()
{
	Renderer.Update();
}

void Engine::OnRender()
{
	Renderer.Render();
}

void Engine::OnRelease()
{
	Renderer.Release();
}
