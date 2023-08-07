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

		// ����̽�, ����̽� ���ؽ�Ʈ ����
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
			MessageBox(m_hWnd, L"����̽� �� ����̽� ���ؽ�Ʈ ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = _device.As(&m_Device);

		// hr = _device->QueryInterface(
		// 	__uuidof(ID3D11Device5),
		// 	&m_Device
		// );

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"����̽� ĳ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
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
			MessageBox(m_hWnd, L"��Ƽ ���ø� ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = _context.As(&m_DeviceContext);

		// hr = _context->QueryInterface(
		// 	__uuidof(ID3D11DeviceContext4),
		// 	&m_DeviceContext
		// );

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"����̽� ���ؽ�Ʈ ĳ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
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

		/// ���� ü�� ����
		DXGI_SWAP_CHAIN_DESC1 dxgiSwapChainDesc1{};
		ZeroMemory(&dxgiSwapChainDesc1, sizeof(dxgiSwapChainDesc1));
		dxgiSwapChainDesc1.Width = 0;										// ����ü�� �ʺ�
		dxgiSwapChainDesc1.Height = 0;										// ����ü�� ����
		dxgiSwapChainDesc1.Format = DXGI_FORMAT_B8G8R8A8_UNORM;				// �ȼ� ����
		dxgiSwapChainDesc1.Stereo = false;									// ���׷��� 3D ��� ����

		// ���� ���ø��� �ϴ� ��쿣 ���� ����Ʈ�� DXGI_SWAP_EFFECT_DISCARD�� �ؾ���.
		// if (m_msaaQuality)
		// {
		// 	dxgiSwapChainDesc1.SampleDesc.Count = 4;						// ��Ƽ���ø� ���� ��
		// 	dxgiSwapChainDesc1.SampleDesc.Quality = m_msaaQuality - 1;		// ��Ƽ���ø� ǰ�� ����
		// 	dxgiSwapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;		// ���� ����Ʈ
		// }
		// else
		// {
			dxgiSwapChainDesc1.SampleDesc.Count = 1;						// ��Ƽ���ø� ���� ��
			dxgiSwapChainDesc1.SampleDesc.Quality = 0;						// ��Ƽ���ø� ǰ�� ����
			dxgiSwapChainDesc1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;	// ���� ����Ʈ	// �� ��쿡 format�� B8G8R8A8, R8G8B8A8�� �ؾ���
		// }

		dxgiSwapChainDesc1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;	// ���� ��� �뵵
		dxgiSwapChainDesc1.BufferCount = 2;									// ����� ����
		dxgiSwapChainDesc1.Scaling = DXGI_SCALING_STRETCH;					// �����ϸ� ���
		dxgiSwapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;			// ���� ���� ���
		dxgiSwapChainDesc1.Flags = 0;

		/// D11 ����̽����� DXGI ����̽��� ����
		Comptr<IDXGIDevice3> dxgiDevice3{};
		hr = m_Device.As(&dxgiDevice3);
		// hr = m_Device->QueryInterface(__uuidof(IDXGIDevice3), (void**)&dxgiDevice3);

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"d3d11����̽��� dxgi����̽��� ĳ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = dxgiDevice3->SetMaximumFrameLatency(1);						// �������� ���� ť�� ����� �� �ִ� ������ ��

		/// ����̽����� ��͸� �޾ƿ�
		Comptr<IDXGIAdapter> dxgiAdapter{};
		dxgiDevice3->GetAdapter(&dxgiAdapter);

		/// ��� ��ȭ~
		Comptr<IDXGIAdapter2> dxgiAdapter2{};
		hr = dxgiAdapter.As(&dxgiAdapter2);
		// dxgiAdapter->QueryInterface(__uuidof(IDXGIAdapter2), (void**)&dxgiAdapter2);

		/// ��Ϳ��� ���丮�� ����
		Comptr<IDXGIFactory3> dxgiFactory3{};
		dxgiAdapter2->GetParent(__uuidof(IDXGIFactory3), (void**)&dxgiFactory3);

		/// ���丮�� ����ü�� ����
		Comptr<IDXGISwapChain1> swapchain{};
		hr = dxgiFactory3->CreateSwapChainForHwnd(
			m_Device.Get(),										// ����̽�
			m_hWnd,											// ���â �ڵ� 
			&dxgiSwapChainDesc1,							// ����ü�� ����
			nullptr,										// ��üȭ�� ����
			nullptr,										// ���ѵ� ��� ���
			&swapchain										// ������ ���� ����
		);

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"����ü�� ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
			return hr;
		}

		hr = swapchain.As(&m_SwapChain);
		// hr = swapchain->QueryInterface(
		// 	__uuidof(IDXGISwapChain2), 
		// 	(void**)&m_SwapChain
		// );

		if (FAILED(hr))
		{
			MessageBox(m_hWnd, L"����ü�� ĳ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
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
			MessageBox(m_hWnd, L"���� ü�����κ��� ���۹��� �������� ���߽��ϴ�.", L"����Ʈ ����", MB_OK | MB_ICONWARNING);
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
			MessageBox(m_hWnd, L"���� ü�����κ��� ���۹��� �������� ���߽��ϴ�.", L"����Ʈ ����", MB_OK | MB_ICONWARNING);
			return hr;
		}

		D3D11_TEXTURE2D_DESC backBufferDesc;

		ZeroMemory(&backBufferDesc, sizeof(backBufferDesc));
		backbuffer->GetDesc(&backBufferDesc);

		float aspectRatioX = static_cast<float>(backBufferDesc.Width) / static_cast<float>(backBufferDesc.Height);
		float aspectRatioY = aspectRatioX < (16.0f / 9.0f) ? aspectRatioX / (16.0f / 9.0f) : 1.0f;

		// ���� ��Ʈ����
		_camera->CameraPerspectiveFovLH(
			2.0f * std::atan(std::tan(ToRadian(70) * 0.5f) / aspectRatioY),
			aspectRatioX,
			0.01f,
			10000.0f
		);

		_camera->CameraOrthographicLH(backBufferDesc.Width, backBufferDesc.Height, 0.01f, 10000.f);
	}
}