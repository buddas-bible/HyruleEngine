#include "DX11Graphics.h"
// 아마 그래픽스 구현 부

#include "DXDevice.h"
#include "DXRenderTarget.h"
#include "DXRasterizerState.h"

namespace Hyrule
{
	extern "C"
	{
		__declspec(dllexport) IRenderer* CreateRenderer()
		{
			return new DX11Graphics;
		}

		__declspec(dllexport) void ReleaseRenderer(IRenderer*& _renderer)
		{
			if (_renderer != nullptr)
			{
				delete _renderer;
			}
		}
	}

	DX11Graphics::DX11Graphics()
		: m_hWnd(),
		m_Device(), m_RenderTarget(), m_RasterizerState()
	{

	}

	DX11Graphics::~DX11Graphics()
	{

	}

	long DX11Graphics::Initialize(int _hwnd)
	{
		m_hWnd = _hwnd;

		HRESULT hr = S_OK;

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

		return hr;
	}

	void DX11Graphics::Finalize()
	{
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

	void DX11Graphics::Render()
	{
		m_RenderTarget->Clear();

		///

		///

		m_Device->Present();
	}

	long DX11Graphics::OnResize()
	{
		HRESULT hr = S_OK;

		hr = m_RenderTarget->OnResize();

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	long DX11Graphics::CreateDeviceAndSwapChain()
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

	long DX11Graphics::CreateRenderTargetAndDepthStencil()
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

	long DX11Graphics::CreateRasterState()
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


}