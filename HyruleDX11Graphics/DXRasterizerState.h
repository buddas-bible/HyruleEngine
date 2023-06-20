#pragma once

class DXDevice;
struct ID3D11RasterizerState2;

class DXRasterizerState
{
public:
	DXRasterizerState(DXDevice* _device);
	~DXRasterizerState();

private:
	DXDevice* m_device;

	ID3D11RasterizerState2* m_currRasterizerState;			// 현재 레스터 상태
	ID3D11RasterizerState2* m_solidRasterizerState;			// 채우는 레스터 상태
	ID3D11RasterizerState2* m_wireRasterizerState;			// 선 레스터라이즈 상태

public:
	int CreateRasterizerState();

	ID3D11RasterizerState2* GetRasterizerState();
	void SetSolidState();
	void SetWireState();
};

