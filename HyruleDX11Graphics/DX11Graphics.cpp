#include "DX11Graphics.h"
// 아마 그래픽스 구현 부

#include "framework.h"

namespace Hyrule
{
	DX11Graphics::~DX11Graphics()
	{

	}


	int DX11Graphics::Initialize(int _hwnd)
	{
		m_hWnd = _hwnd;

		HRESULT hr = S_OK;

		hr = CreateDevice();
		hr = CreateSwapChain();
		hr = CreateRenderTargetView();
		hr = CreateDepthStencilView();
		hr = CreateRasterState();

		return (int)hr;
	}

	void DX11Graphics::Finalize()
	{
		Release(device);
		Release(deviceContext);
		Release(swapChain);
		Release(backBuffer);
		Release(renderTargetView);
		Release(depthStencil);
		Release(depthStencilView);
		Release(currRasterizerState);
		Release(solidRasterizerState);
		Release(wireRasterizerState);
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

	int DX11Graphics::CreateDevice()
	{
		HRESULT hr = S_OK;

		UINT creationFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL FeatureLevels[] = {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		// 디바이스, 디바이스 컨텍스트 생성
		hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,
			FeatureLevels,
			ARRAYSIZE(FeatureLevels),
			D3D11_SDK_VERSION,
			&device,
			nullptr,
			&deviceContext);

		return (int)hr;
	}

	int DX11Graphics::CreateSwapChain()
	{
		HRESULT hr = S_OK;

		// 스왑 체인 설정
		DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc1{};
		ZeroMemory(&dxgiSwapChainDesc1, sizeof(dxgiSwapChainDesc1));
		dxgiSwapChainDesc1.Width = 0;
		dxgiSwapChainDesc1.Height = 0;
		dxgiSwapChainDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		dxgiSwapChainDesc1.Stereo = false;
		dxgiSwapChainDesc1.SampleDesc.Count = 1;
		dxgiSwapChainDesc1.SampleDesc.Quality = 0;
		dxgiSwapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		dxgiSwapChainDesc1.BufferCount = 2;
		dxgiSwapChainDesc1.Scaling = DXGI_SCALING_NONE;
		dxgiSwapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; // 이 경우에 format은 B8G8R8A8, R8G8B8A8로 해ㅑ함
		dxgiSwapChainDesc1.Flags = 0;

		// 임시 포인터 생성
		ComPtr<IDXGIDevice2> device2;
		m_pd3dDevice.As(&device2);

		device2->SetMaximumFrameLatency(1);

		// 디바이스로 어뎁터를 가져옴
		ComPtr<IDXGIAdapter> adapter;
		device2->GetAdapter(&adapter);

		// 어뎁터에서 팩토리를 만듬
		ComPtr<IDXGIFactory2> factory2;
		adapter->GetParent(
			__uuidof(IDXGIFactory2),
			&factory2
		);

		// HWND로 스왑체인 생성
		ComPtr<IDXGISwapChain1> swapChain1;
		hr = factory2->CreateSwapChainForHwnd(
			m_pd3dDevice.Get(),
			m_hWnd,
			&dxgiSwapChainDesc1,
			NULL,
			NULL,
			&swapChain1
		);

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

	int DX11Graphics::CreateRasterState()
	{
		HRESULT hr = S_OK;


		return (int)hr;
	}
}