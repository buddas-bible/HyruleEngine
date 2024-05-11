#pragma once
#include "framework.h"

struct ID3D11Device5;
struct ID3D11DeviceContext4;
struct IDXGISwapChain2;

namespace hyrule
{
	class DXCamera;
	
	class DXDevice
	{
	public:
		DXDevice(HWND _hwnd);
		~DXDevice();

	private:
		HWND					m_hWnd;
		UINT					m_msaaQuality;
	
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		Comptr<ID3D11Device5>			m_Device;					// 디바이스
		Comptr<ID3D11DeviceContext4>	m_DeviceContext;			// 디바이스컨텍스트
		Comptr<IDXGISwapChain2>			m_SwapChain;				// 스왑체인

		D3D_FEATURE_LEVEL				m_FeatureLevels;			// 피처 레벨
		DXGI_PRESENT_PARAMETERS			m_PresentParameter;
		D3D11_VIEWPORT					m_viewport;

	public:
		ID3D11Device5*			GetDevice();
		ID3D11DeviceContext4*	GetDeviceContext();
		IDXGISwapChain2*		GetSwapChain();

		void					Present();

		HRESULT					CreateDeviceAndSwapChain();

		HRESULT					SetViewport();
		HRESULT					SetCamera(DXCamera*);

	private:
		HRESULT					CreateDevice();
		HRESULT					CreateSwapChain();
	};
}
