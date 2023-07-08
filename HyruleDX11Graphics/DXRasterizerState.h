#pragma once
#include "framework.h"

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
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		DXDevice* m_device;

		Comptr<ID3D11RasterizerState2> m_currRasterizerState;			// ���� ������ ����
		Comptr<ID3D11RasterizerState2> m_solidRasterizerState;			// ä��� ������ ����
		Comptr<ID3D11RasterizerState2> m_wireRasterizerState;			// �� �����Ͷ����� ����

	public:
		int CreateRasterizerState();

		ID3D11RasterizerState2* GetCurrRasterizerState();
		ID3D11RasterizerState2* GetSolidRasterizerState();
		ID3D11RasterizerState2* GetWireRasterizerState();
		void SetSolidState();
		void SetWireState();
	};
}