#include "DXDevice.h"


DXDevice::DXDevice(HWND _hwnd) : 
	m_hWnd(_hwnd), m_msaaQuality(),
	m_Device(), m_DeviceContext(), m_SwapChain()
{

}

DXDevice::~DXDevice()
{
	Release(m_SwapChain);
	Release(m_DeviceContext);
	Release(m_Device);
}

ID3D11Device5* DXDevice::GetDevice()
{
	return m_Device;
}

ID3D11DeviceContext4* DXDevice::GetDeviceContext()
{
	return m_DeviceContext;
}

IDXGISwapChain2* DXDevice::GetSwapChain()
{
	return m_SwapChain;
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

	ID3D11Device* _device = nullptr;
	ID3D11DeviceContext* _context = nullptr;

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

	hr = _device->QueryInterface(
		__uuidof(ID3D11Device5),
		reinterpret_cast<void**>(&m_Device)
	);

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

	hr = _context->QueryInterface(
		__uuidof(ID3D11DeviceContext4),
		reinterpret_cast<void**>(&m_DeviceContext)
	);

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
	dxgiSwapChainDesc1.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;			// ���� ������ ���
	dxgiSwapChainDesc1.Flags = 0;

	/// D11 ����̽����� DXGI ����̽��� ����
	IDXGIDevice3* dxgiDevice3;
	hr = m_Device->QueryInterface(__uuidof(IDXGIDevice3), (void**)&dxgiDevice3);

	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"d3d11����̽��� dxgi����̽��� ĳ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
		return hr;
	}

	hr = dxgiDevice3->SetMaximumFrameLatency(1);						// �������� ���� ť�� ����� �� �ִ� ������ ��

	/// ����̽����� ��͸� �޾ƿ�
	IDXGIAdapter* dxgiAdapter;
	dxgiDevice3->GetAdapter(&dxgiAdapter);

	/// ��� ��ȭ~
	IDXGIAdapter2* dxgiAdapter2;
	dxgiAdapter->QueryInterface(__uuidof(IDXGIAdapter2), (void**)&dxgiAdapter2);

	/// ��Ϳ��� ���丮�� ����
	IDXGIFactory3* dxgiFactory3;
	dxgiAdapter2->GetParent(__uuidof(IDXGIFactory3), (void**)&dxgiFactory3);

	/// ���丮�� ����ü�� ����
	IDXGISwapChain1* swapchain;
	hr = dxgiFactory3->CreateSwapChainForHwnd(
		m_Device,										// ����̽�
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

	hr = swapchain->QueryInterface(
		__uuidof(IDXGISwapChain2), 
		(void**)&m_SwapChain
	);

	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"����ü�� ĳ���� ����", L"�ʱ�ȭ ����", MB_OK | MB_ICONWARNING);
		return hr;
	}

	Release(dxgiDevice3);
	Release(dxgiAdapter);
	Release(dxgiAdapter2);
	Release(dxgiFactory3);

	return hr;
}