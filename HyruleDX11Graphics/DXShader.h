#pragma once

class DXDevice;

class DXShader
{
public:
	DXShader(DXDevice* _device);
	~DXShader();

private:
	DXDevice* m_device;

public:
	int CreateVertexShader();
	int CreatePixelShader();
};

