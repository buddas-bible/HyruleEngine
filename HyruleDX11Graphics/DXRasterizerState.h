#pragma once

struct ID3D11RasterizerState2;

namespace Hyrule
{
	class DXDevice;

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

		ID3D11RasterizerState2* GetCurrRasterizerState();
		ID3D11RasterizerState2* GetSolidRasterizerState();
		ID3D11RasterizerState2* GetWireRasterizerState();
		void SetSolidState();
		void SetWireState();
	};
}