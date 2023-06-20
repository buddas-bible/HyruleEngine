#include "DX11Graphics.h"
// 아마 그래픽스 구현 부

#include "framework.h"
#include "DXDevice.h"
#include "DXRenderTarget.h"
#include "DXRasterizerState.h"

namespace Hyrule
{
	DX11Graphics::~DX11Graphics()
	{

	}


	int DX11Graphics::Initialize(int _hwnd)
	{
		m_hWnd = _hwnd;

		HRESULT hr = S_OK;

		// hr = CreateDevice();
		// hr = CreateSwapChain();
		// hr = CreateRenderTargetView();
		// hr = CreateDepthStencilView();

		hr = CreateDeviceAndSwapChain();

		if (FAILED(hr))
		{
			return (int)hr;
		}


		hr = CreateRasterState();

		return (int)hr;
	}

	void DX11Graphics::Finalize()
	{
		if (m_Device)
		{
			delete m_Device;
			m_Device = nullptr;
		}
		if (m_RenderTarget)
		{
			delete m_RenderTarget;
			m_RenderTarget = nullptr;
		}
		if (m_RasterizerState)
		{
			delete m_RasterizerState;
			m_RasterizerState = nullptr;
		}
	}

	void DX11Graphics::Update()
	{

	}

	void DX11Graphics::Render()
	{

	}

	int DX11Graphics::OnResize()
	{
		HRESULT hr = S_OK;


		return (int)hr;
	}


	int DX11Graphics::CreateDeviceAndSwapChain()
	{
		HRESULT hr = S_OK;
		m_Device = new DXDevice((HWND)m_hWnd);

		hr = m_Device->CreateDeviceAndSwapChain();

		if (FAILED(hr))
		{
			return hr;
		}

		return (int)hr;
	}


	int DX11Graphics::CreateRenderTargetAndDepthStencil()
	{
		HRESULT hr = S_OK;
		m_RenderTarget = new DXRenderTarget(m_Device);

		hr = m_RenderTarget->CreateRenderTargetAndDepthStencil();

		if (FAILED(hr))
		{
			return hr;
		}

		return (int)hr;
	}

	/*
	int DX11Graphics::CreateDevice()
	{
		HRESULT hr = S_OK;

		// UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
		// 
#if defi// ned(_DEBUG)
		// creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif	// 
		// 
		// D3D_FEATURE_LEVEL FeatureLevels[] = {
		// 	D3D_FEATURE_LEVEL_11_1,
		// 	D3D_FEATURE_LEVEL_11_0,
		// 	D3D_FEATURE_LEVEL_10_1,
		// 	D3D_FEATURE_LEVEL_10_0,
		// 	D3D_FEATURE_LEVEL_9_3,
		// 	D3D_FEATURE_LEVEL_9_2,
		// 	D3D_FEATURE_LEVEL_9_1
		// };
		// 
		// ID3D11Device* _device = nullptr;
		// ID3D11DeviceContext* _context = nullptr;
		// 
		// // 디바이스, 디바이스 컨텍스트 생성
		// hr = D3D11CreateDevice(
		// 	nullptr,
		// 	D3D_DRIVER_TYPE_HARDWARE,
		// 	nullptr,
		// 	creationFlags,
		// 	FeatureLevels,
		// 	ARRAYSIZE(FeatureLevels),
		// 	D3D11_SDK_VERSION,
		// 	&_device,
		// 	nullptr,
		// 	&_context
		// );
		// 
		// if (FAILED(hr))
		// {
		// 	return hr;
		// }
		// 
		// hr = _device->QueryInterface(
		// 	__uuidof(ID3D11Device5), 
		// 	reinterpret_cast<void**>(&m_device)
		// );
		// 
		// if (FAILED(hr))
		// {
		// 	return hr;
		// }
		// 
		// hr = m_device->CheckMultisampleQualityLevels1(
		// 	DXGI_FORMAT_B8G8R8A8_UNORM,
		// 	4,
		// 	D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE,
		// 	(UINT*)&m_msaaQuality
		// );
		// 
		// if (FAILED(hr))
		// {
		// 	return hr;
		// }
		// 
		// hr = _context->QueryInterface(
		// 	__uuidof(ID3D11DeviceContext4),
		// 	reinterpret_cast<void**>(&m_deviceContext)
		// );

		return (int)hr;
	}

	int DX11Graphics::CreateSwapChain()
	{
		HRESULT hr = S_OK;

		// /// 스왑 체인 설정
		// DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc1{};
		// ZeroMemory(&dxgiSwapChainDesc1, sizeof(dxgiSwapChainDesc1));
		// dxgiSwapChainDesc1.Width = 0;										// 스왑체인 너비
		// dxgiSwapChainDesc1.Height = 0;										// 스왑체인 높이
		// dxgiSwapChainDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// 픽셀 형식
		// dxgiSwapChainDesc1.Stereo = false;									// 스테레오 3D 사용 여부
		// 
		// // 다중 샘플링을 하는 경우엔 스왑 이펙트도 DXGI_SWAP_EFFECT_DISCARD로 해야함.
		// if (m_msaaQuality)
		// {
		// 	dxgiSwapChainDesc1.SampleDesc.Count = 4;						// 멀티샘플링 샘플 수
		// 	dxgiSwapChainDesc1.SampleDesc.Quality = m_msaaQuality - 1;		// 멀티샘플링 품질 수준
		// 	dxgiSwapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		// 스왑 이펙트
		// }
		// else
		// {
		// 	dxgiSwapChainDesc1.SampleDesc.Count = 1;						// 멀티샘플링 샘플 수
		// 	dxgiSwapChainDesc1.SampleDesc.Quality = 0;						// 멀티샘플링 품질 수준
		// 	dxgiSwapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// 스왑 이펙트	// 이 경우에 format은 B8G8R8A8, R8G8B8A8로 해야함
		// }
		// 
		// dxgiSwapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 버퍼 사용 용도
		// dxgiSwapChainDesc1.BufferCount = 2;									// 백버퍼 개수
		// dxgiSwapChainDesc1.Scaling = DXGI_SCALING_STRETCH;						// 스케일링 모드
		// dxgiSwapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;			// 알파 블렌딩 모드
		// dxgiSwapChainDesc1.Flags = 0;										// 

		/// 임시 포인터 생성
		// ComPtr<IDXGIDevice2> device2;
		// m_pd3dDevice.As(&device2);
		// IDXGIDevice2* dxDevice;
		// dxDevice = m_device;
		
		// device2->SetMaximumFrameLatency(1);

		/// 디바이스로 어뎁터를 가져옴
		// ComPtr<IDXGIAdapter> adapter;
		// device2->GetAdapter(&adapter);

		/// 어뎁터에서 팩토리를 만듬
		// ComPtr<IDXGIFactory2> factory2;
		// adapter->GetParent(
		// 	__uuidof(IDXGIFactory2),
		// 	&factory2
		// );

		/// HWND로 스왑체인 생성
		// ComPtr<IDXGISwapChain1> swapChain1;
		// hr = factory2->CreateSwapChainForHwnd(
		// 	m_pd3dDevice.Get(),
		// 	m_hWnd,
		// 	&dxgiSwapChainDesc1,
		// 	NULL,
		// 	NULL,
		// 	&swapChain1
		// );

		return (int)hr;
	}

	int DX11Graphics::CreateRenderTargetView()
	{
		HRESULT hr = S_OK;


		return (int)hr;
	}

	int DX11Graphics::CreateDepthStencilView()
	{
		HRESULT hr = S_OK;


		return (int)hr;
	}
	*/

	int DX11Graphics::CreateRasterState()
	{
		HRESULT hr = S_OK;


		return (int)hr;
	}
}