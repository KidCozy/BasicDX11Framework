#pragma once
class VirtualObject
{
private:
	virtual void OnInit() = 0;
	virtual void OnUpdate() = 0;
	virtual void OnRender() = 0;
	virtual void OnRelease() = 0;

public:

	virtual void Init() { OnInit(); }
	virtual void Update() { OnUpdate(); }
	virtual void Render() { OnRender(); }
	virtual void Release() { OnRelease(); }



	VirtualObject();
	virtual ~VirtualObject();
};

