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

		Comptr<ID3D11RasterizerState2> m_currRasterizerState;			// 현재 레스터 상태
		Comptr<ID3D11RasterizerState2> m_solidRasterizerState;			// 채우는 레스터 상태
		Comptr<ID3D11RasterizerState2> m_wireRasterizerState;			// 선 레스터라이즈 상태

	public:
		int CreateRasterizerState();

		ID3D11RasterizerState2* GetCurrRasterizerState();
		ID3D11RasterizerState2* GetSolidRasterizerState();
		ID3D11RasterizerState2* GetWireRasterizerState();
		void SetSolidState();
		void SetWireState();
	};
}