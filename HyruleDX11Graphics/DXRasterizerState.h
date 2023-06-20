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

	ID3D11RasterizerState2* m_currRasterizerState;			// ���� ������ ����
	ID3D11RasterizerState2* m_solidRasterizerState;			// ä��� ������ ����
	ID3D11RasterizerState2* m_wireRasterizerState;			// �� �����Ͷ����� ����

public:
	int CreateRasterizerState();

	ID3D11RasterizerState2* GetRasterizerState();
	void SetSolidState();
	void SetWireState();
};

