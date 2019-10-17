struct ID3D11Device;
class DeviceSingle;
class DeviceSingle
{
private:
	static DeviceSingle* Instance_;
	DeviceSingle() { }
	~DeviceSingle() {}
public:
	ID3D11Device* Device;
public:


	static DeviceSingle* GetInstance() { if (Instance_ == nullptr) Instance_ = new DeviceSingle(); return Instance_; }
};

