#include "HyruleGraphicsDX11.h"
// 아마 그래픽스 구현 부

#include "DXDevice.h"
#include "DXRenderTarget.h"
#include "DXRasterizerState.h"
#include "ICamera.h"
#include "DXCamera.h"


namespace Hyrule
{
	extern "C"
	{
		__declspec(dllexport) IGraphics* CreateRenderer()
		{
			return new HyruleGraphicsDX11;
		}
	}

	HyruleGraphicsDX11::HyruleGraphicsDX11()
		: m_hWnd(),
		m_Device(), m_RenderTarget(), m_RasterizerState()
	{

	}

	HyruleGraphicsDX11::~HyruleGraphicsDX11()
	{

	}

	long HyruleGraphicsDX11::Initialize(int _hwnd)
	{
		m_hWnd = _hwnd;

		HRESULT hr = S_OK;

		hr = CreateCamera();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = CreateDeviceAndSwapChain();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = CreateRenderTargetAndDepthStencil();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = CreateRasterState();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = CreateCamera();

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	void HyruleGraphicsDX11::Finalize()
	{
		if (m_camera)
		{
			delete m_camera;
			m_camera = nullptr;
		}
		if (m_RasterizerState)
		{
			delete m_RasterizerState;
			m_RasterizerState = nullptr;
		}
		if (m_RenderTarget)
		{
			delete m_RenderTarget;
			m_RenderTarget = nullptr;
		}
		if (m_Device)
		{
			delete m_Device;
			m_Device = nullptr;
		}
	}

	void HyruleGraphicsDX11::Render()
	{
		m_RenderTarget->Clear();

		///

		///

		m_Device->Present();
	}

	long HyruleGraphicsDX11::OnResize()
	{
		HRESULT hr = S_OK;

		hr = m_RenderTarget->OnResize();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = m_Device->SetCamera(m_camera);

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	ICamera* HyruleGraphicsDX11::GetCamera()
	{
		if (m_camera != nullptr)
		{
			return (ICamera*)m_camera;
		}

		return nullptr;
	}

	long HyruleGraphicsDX11::CreateDeviceAndSwapChain()
	{
		HRESULT hr = S_OK;
		m_Device = new DXDevice((HWND)m_hWnd);

		hr = m_Device->CreateDeviceAndSwapChain();

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	long HyruleGraphicsDX11::CreateRenderTargetAndDepthStencil()
	{
		HRESULT hr = S_OK;

		m_RenderTarget = new DXRenderTarget(m_Device);

		hr = m_RenderTarget->CreateRenderTargetAndDepthStencil();

		if (FAILED(hr))
		{
			return hr;
		}

		m_RenderTarget->Bind();

		return hr;
	}

	long HyruleGraphicsDX11::CreateRasterState()
	{
		HRESULT hr = S_OK;
		m_RasterizerState = new DXRasterizerState(m_Device);

		hr = m_RasterizerState->CreateRasterizerState();

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	long HyruleGraphicsDX11::CreateCamera()
	{
		if (m_camera != nullptr)
		{
			delete m_camera;
			m_camera = nullptr;
		}

		m_camera = new DXCamera;

		m_Device->SetCamera(m_camera);
		
		return S_OK;
	}
}