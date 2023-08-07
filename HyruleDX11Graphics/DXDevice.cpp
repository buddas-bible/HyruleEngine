#include "DXDevice.h"
#include "DXCamera.h"

namespace Hyrule
{
	DXDevice::DXDevice(HWND _hwnd) :
		m_hWnd(_hwnd), m_msaaQuality(),
		m_Device(), m_DeviceContext(), m_SwapChain(),
		m_FeatureLevels(), m_PresentParameter(), m_viewport()
	{

	}

	DXDevice::~DXDevice()
	{

	}

	ID3D11Device5* DXDevice::GetDevice()
	{
		return m_Device.Get();
	}

	ID3D11DeviceContext4* DXDevice::GetDeviceContext()
	{
		return m_DeviceContext.Get();
	}

	IDXGISwapChain2* DXDevice::GetSwapChain()
	{
		return m_SwapChain.Get();
	}

	void DXDevice::Present()
	{
	#ifdef _DEBUG
		m_SwapChain->Present1(0, 0, &m_PresentParameter);
	#else
		m_SwapChain->Present(0, 0);
	#endif // DEBUG
	}

	HRESULT DXDevice::CreateDeviceAndSwapChain()
	{
		HRESULT hr = S_OK;

		hr = CreateDevice();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = CreateSwapChain();

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	HRESULT DXDevice::CreateDevice()
	{
		HRESULT hr = S_OK;

		UINT creationFlags{ D3D11_CREATE_DEVICE_BGRA_SUPPORT };

	#if defined(_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
	#endif

		D3D_FEATURE_LEVEL FeatureLevels[] {
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
			D3D_FEATURE_LEVEL_9_3,
			D3D_FEATURE_LEVEL_9_2,
			D3D_FEATURE_LEVEL_9_1
		};

		Comptr<ID3D11Device> _device{};
		Comptr<ID3D11DeviceContext> _context{};

		// 디바이스, 디바이스 컨텍스트 생성
		hr = D3D11CreateDevice(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			creationFlags,
			FeatureLevels,
			ARRAYSIZE(FeatureLevels),
			D3D11_SDK_VERSION,
			&_device,
			nullptr,
			&_context
		);

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"디바이스 및 디바이스 컨텍스트 생성 실패", L"초기화 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = _device.As(&m_Device);

		// hr = _device->QueryInterface(
		// 	__uuidof(ID3D11Device5),
		// 	&m_Device
		// );

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"디바이스 캐스팅 실패", L"초기화 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		// hr = m_Device->CheckMultisampleQualityLevels1(
		// 	DXGI_FORMAT_B8G8R8A8_UNORM,
		// 	4,
		// 	D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_TILED_RESOURCE,
		// 	&m_msaaQuality
		// );

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"멀티 샘플링 설정 실패", L"초기화 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = _context.As(&m_DeviceContext);

		// hr = _context->QueryInterface(
		// 	__uuidof(ID3D11DeviceContext4),
		// 	&m_DeviceContext
		// );

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"디바이스 컨텍스트 캐스팅 실패", L"초기화 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

	#ifdef _DEBUG
		m_PresentParameter.DirtyRectsCount = 0;
		m_PresentParameter.pDirtyRects = NULL;
		m_PresentParameter.pScrollRect = NULL;
		m_PresentParameter.pScrollOffset = NULL;
	#endif // DEBUG

		return hr;
	}

	HRESULT DXDevice::CreateSwapChain()
	{
		HRESULT hr = S_OK;

		/// 스왑 체인 설정
		DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc1{};
		ZeroMemory(&dxgiSwapChainDesc1, sizeof(dxgiSwapChainDesc1));
		dxgiSwapChainDesc1.Width = 0;										// 스왑체인 너비
		dxgiSwapChainDesc1.Height = 0;										// 스왑체인 높이
		dxgiSwapChainDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// 픽셀 형식
		dxgiSwapChainDesc1.Stereo = false;									// 스테레오 3D 사용 여부

		// 다중 샘플링을 하는 경우엔 스왑 이펙트도 DXGI_SWAP_EFFECT_DISCARD로 해야함.
		// if (m_msaaQuality)
		// {
		// 	dxgiSwapChainDesc1.SampleDesc.Count = 4;						// 멀티샘플링 샘플 수
		// 	dxgiSwapChainDesc1.SampleDesc.Quality = m_msaaQuality - 1;		// 멀티샘플링 품질 수준
		// 	dxgiSwapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		// 스왑 이펙트
		// }
		// else
		// {
			dxgiSwapChainDesc1.SampleDesc.Count = 1;						// 멀티샘플링 샘플 수
			dxgiSwapChainDesc1.SampleDesc.Quality = 0;						// 멀티샘플링 품질 수준
			dxgiSwapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// 스왑 이펙트	// 이 경우에 format은 B8G8R8A8, R8G8B8A8로 해야함
		// }

		dxgiSwapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// 버퍼 사용 용도
		dxgiSwapChainDesc1.BufferCount = 2;									// 백버퍼 개수
		dxgiSwapChainDesc1.Scaling = DXGI_SCALING_STRETCH;					// 스케일링 모드
		dxgiSwapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;			// 알파 블렌딩 모드
		dxgiSwapChainDesc1.Flags = 0;

		/// D11 디바이스에서 DXGI 디바이스를 만듬
		Comptr<IDXGIDevice3> dxgiDevice3{};
		hr = m_Device.As(&dxgiDevice3);
		// hr = m_Device->QueryInterface(__uuidof(IDXGIDevice3), (void**)&dxgiDevice3);

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"d3d11디바이스를 dxgi디바이스로 캐스팅 실패", L"초기화 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = dxgiDevice3->SetMaximumFrameLatency(1);						// 렌더링을 위해 큐에 대기할 수 있는 프레임 수

		/// 디바이스에서 어뎁터를 받아옴
		Comptr<IDXGIAdapter> dxgiAdapter{};
		dxgiDevice3->GetAdapter(&dxgiAdapter);

		/// 어뎁터 진화~
		Comptr<IDXGIAdapter2> dxgiAdapter2{};
		hr = dxgiAdapter.As(&dxgiAdapter2);
		// dxgiAdapter->QueryInterface(__uuidof(IDXGIAdapter2), (void**)&dxgiAdapter2);

		/// 어뎁터에서 펙토리도 받음
		Comptr<IDXGIFactory3> dxgiFactory3{};
		dxgiAdapter2->GetParent(__uuidof(IDXGIFactory3), (void**)&dxgiFactory3);

		/// 팩토리로 스왑체인 만듬
		Comptr<IDXGISwapChain1> swapchain{};
		hr = dxgiFactory3->CreateSwapChainForHwnd(
			m_Device.Get(),										// 디바이스
			m_hWnd,											// 출력창 핸들 
			&dxgiSwapChainDesc1,							// 스왑체인 설정
			nullptr,										// 전체화면 설정
			nullptr,										// 제한된 출력 어뎁터
			&swapchain										// 포인터 받을 변수
		);

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"스왑체인 생성 실패", L"초기화 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = swapchain.As(&m_SwapChain);
		// hr = swapchain->QueryInterface(
		// 	__uuidof(IDXGISwapChain2), 
		// 	(void**)&m_SwapChain
		// );

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"스왑체인 캐스팅 실패", L"초기화 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = SetViewport();

		if (FAILED(hr))
		{
			return hr;
		}

		// Release(dxgiDevice3);
		// Release(dxgiAdapter);
		// Release(dxgiAdapter2);
		// Release(dxgiFactory3);

		return hr;
	}
	
	HRESULT DXDevice::SetViewport()
	{
		HRESULT hr = S_OK;

		Comptr<ID3D11Texture2D> backbuffer{};

		hr = m_SwapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(void**)&backbuffer
		);

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"스왑 체인으로부터 백퍼버를 가져오지 못했습니다.", L"뷰포트 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		D3D11_TEXTURE2D_DESC backBufferDesc;

		ZeroMemory(&backBufferDesc, sizeof(backBufferDesc));
		backbuffer->GetDesc(&backBufferDesc);

		ZeroMemory(&m_viewport, sizeof(m_viewport));
		m_viewport.TopLeftX = 0.f;
		m_viewport.TopLeftY = 0.f;
		m_viewport.Width = static_cast<float>(backBufferDesc.Width);
		m_viewport.Height = static_cast<float>(backBufferDesc.Height);
		m_viewport.MinDepth = D3D11_MIN_DEPTH;
		m_viewport.MaxDepth = D3D11_MAX_DEPTH;

		m_DeviceContext->RSSetViewports(1, &m_viewport);

		return hr;
	}

	HRESULT DXDevice::SetCamera(DXCamera* _camera)
	{
		HRESULT hr = S_OK;

		Comptr<ID3D11Texture2D> backbuffer{};

		hr = m_SwapChain->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(void**)&backbuffer
		);

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"스왑 체인으로부터 백퍼버를 가져오지 못했습니다.", L"뷰포트 오류", MB_OK | MB_ICONWARNING);
			return hr;
		}

		D3D11_TEXTURE2D_DESC backBufferDesc;

		ZeroMemory(&backBufferDesc, sizeof(backBufferDesc));
		backbuffer->GetDesc(&backBufferDesc);

		float aspectRatioX = static_cast<float>(backBufferDesc.Width) / static_cast<float>(backBufferDesc.Height);
		float aspectRatioY = aspectRatioX < (16.0f / 9.0f) ? aspectRatioX / (16.0f / 9.0f) : 1.0f;

		// 투영 매트릭스
		_camera->CameraPerspectiveFovLH(
			2.0f * std::atan(std::tan(ToRadian(70) * 0.5f) / aspectRatioY),
			aspectRatioX,
			0.01f,
			10000.0f
		);

		_camera->CameraOrthographicLH(backBufferDesc.Width, backBufferDesc.Height, 0.01f, 10000.f);
	}
}