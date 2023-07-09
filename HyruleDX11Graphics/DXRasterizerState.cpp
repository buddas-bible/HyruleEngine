#include "DXRasterizerState.h"

#include "DXDevice.h"

namespace Hyrule
{
	DXRasterizerState::DXRasterizerState(std::shared_ptr<DXDevice> _device)
		: m_device(_device),
		m_currRasterizerState(), m_solidRasterizerState(), m_wireRasterizerState()
	{

	}

	int DXRasterizerState::CreateRasterizerState()
	{
		HRESULT hr = S_OK;

		D3D11_RASTERIZER_DESC2 solidRasterDesc;					// 채우는 모드
		ZeroMemory(&solidRasterDesc, sizeof(D3D11_RASTERIZER_DESC2));
		solidRasterDesc.FillMode = D3D11_FILL_SOLID;			// 채우기 모드
		solidRasterDesc.CullMode = D3D11_CULL_BACK;				// 지정된 방향은 그리지 않음 (BACK이니 뒷면은 그리지 않음)	
		solidRasterDesc.FrontCounterClockwise = false;			// 시계방향으로 할 거임
		solidRasterDesc.DepthClipEnable = true;					// 거리에 따라 클리핑을 할지

		hr = m_device->GetDevice()->CreateRasterizerState2(
			&solidRasterDesc,
			&m_solidRasterizerState
		);

		if (FAILED(hr))
		{
			return hr;
		}

		D3D11_RASTERIZER_DESC2 wireRasterDesc;						// 채우지 않는 모드
		ZeroMemory(&wireRasterDesc, sizeof(D3D11_RASTERIZER_DESC2));
		wireRasterDesc.FillMode = D3D11_FILL_WIREFRAME;				// 채우기 모드
		wireRasterDesc.CullMode = D3D11_CULL_NONE;					// 지정된 방향은 그리지 않음
		wireRasterDesc.FrontCounterClockwise = false;				// 시계방향으로 할 거임
		wireRasterDesc.DepthClipEnable = true;						// 거리에 따라 클리핑을 할지

		hr = m_device->GetDevice()->CreateRasterizerState2(
			&wireRasterDesc,
			&m_wireRasterizerState
		);

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	ID3D11RasterizerState2* DXRasterizerState::GetCurrRasterizerState()
	{
		return m_currRasterizerState.Get();
	}

	ID3D11RasterizerState2* DXRasterizerState::GetSolidRasterizerState()
	{
		return m_solidRasterizerState.Get();
	}

	ID3D11RasterizerState2* DXRasterizerState::GetWireRasterizerState()
	{
		return m_wireRasterizerState.Get();
	}

	void DXRasterizerState::SetSolidState()
	{
		m_currRasterizerState = m_solidRasterizerState;
	}

	void DXRasterizerState::SetWireState()
	{
		m_currRasterizerState = m_wireRasterizerState;
	}
}