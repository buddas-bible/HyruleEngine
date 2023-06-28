#pragma once
#include "framework.h"

class DXDevice
{
public:
	DXDevice(HWND _hwnd);
	~DXDevice();

private:
	HWND&					m_hWnd;
	UINT					m_msaaQuality;

	ID3D11Device5*			m_Device;					// 디바이스
	ID3D11DeviceContext4*	m_DeviceContext;			// 디바이스컨텍스트
	IDXGISwapChain2*		m_SwapChain;				// 스왑체인

	D3D_FEATURE_LEVEL		m_FeatureLevels{};			// 피처 레벨
	DXGI_PRESENT_PARAMETERS m_PresentParameter{};

public:
	ID3D11Device5*			GetDevice();
	ID3D11DeviceContext4*	GetDeviceContext();
	IDXGISwapChain2*		GetSwapChain();

	void					Present();

	HRESULT					CreateDeviceAndSwapChain();

private:
	HRESULT					CreateDevice();
	HRESULT					CreateSwapChain();
};

