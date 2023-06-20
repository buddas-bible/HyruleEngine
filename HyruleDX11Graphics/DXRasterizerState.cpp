#include "DXRasterizerState.h"
#include "framework.h"

#include "DXDevice.h"

DXRasterizerState::DXRasterizerState(DXDevice* _device)
	: m_device(_device),
	m_currRasterizerState(), m_solidRasterizerState(), m_wireRasterizerState()
{

}

DXRasterizerState::~DXRasterizerState()
{
	Release(m_currRasterizerState);
	Release(m_wireRasterizerState);
	Release(m_solidRasterizerState);
}

int DXRasterizerState::CreateRasterizerState()
{
	HRESULT hr = S_OK;

	D3D11_RASTERIZER_DESC2 solidRasterDesc;					// ä��� ���
	ZeroMemory(&solidRasterDesc, sizeof(D3D11_RASTERIZER_DESC2));
	solidRasterDesc.FillMode = D3D11_FILL_SOLID;			// ä��� ���
	solidRasterDesc.CullMode = D3D11_CULL_BACK;				// ������ ������ �׸��� ���� (BACK�̴� �޸��� �׸��� ����)	
	solidRasterDesc.FrontCounterClockwise = false;			// �ð�������� �� ����
	solidRasterDesc.DepthClipEnable = true;					// �Ÿ��� ���� Ŭ������ ����

	hr = m_device->GetDevice()->CreateRasterizerState2(
		&solidRasterDesc,
		&m_solidRasterizerState
	);

	if (FAILED(hr))
	{
		return hr;
	}

	D3D11_RASTERIZER_DESC2 wireRasterDesc;						// ä���� �ʴ� ���
	ZeroMemory(&wireRasterDesc, sizeof(D3D11_RASTERIZER_DESC2));
	wireRasterDesc.FillMode = D3D11_FILL_WIREFRAME;				// ä��� ���
	wireRasterDesc.CullMode = D3D11_CULL_NONE;					// ������ ������ �׸��� ����
	wireRasterDesc.FrontCounterClockwise = false;				// �ð�������� �� ����
	wireRasterDesc.DepthClipEnable = true;						// �Ÿ��� ���� Ŭ������ ����

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
	return m_currRasterizerState;
}

ID3D11RasterizerState2* DXRasterizerState::GetSolidRasterizerState()
{
	return m_solidRasterizerState;
}

ID3D11RasterizerState2* DXRasterizerState::GetWireRasterizerState()
{
	return m_wireRasterizerState;
}

void DXRasterizerState::SetSolidState()
{
	m_currRasterizerState = m_solidRasterizerState;
}

void DXRasterizerState::SetWireState()
{
	m_currRasterizerState = m_wireRasterizerState;
}