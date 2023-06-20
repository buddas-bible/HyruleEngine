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

		hr = CreateDeviceAndSwapChain();

		if (FAILED(hr))
		{
			return (int)hr;
		}

		hr = CreateRenderTargetAndDepthStencil();

		if (FAILED(hr))
		{
			return (int)hr;
		}

		hr = CreateRasterState();

		if (FAILED(hr))
		{
			return (int)hr;
		}

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

	void DX11Graphics::Render()
	{
		m_RenderTarget->Clear();

		///

		///

		m_Device->Present();
	}

	int DX11Graphics::OnResize()
	{
		HRESULT hr = S_OK;

		hr = m_RenderTarget->OnResize();

		if (FAILED(hr))
		{
			return (int)hr;
		}

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

		m_RenderTarget->Bind();

		return (int)hr;
	}

	int DX11Graphics::CreateRasterState()
	{
		HRESULT hr = S_OK;
		m_RasterizerState = new DXRasterizerState(m_Device);

		hr = m_RasterizerState->CreateRasterizerState();

		if (FAILED(hr))
		{
			return hr;
		}

		return (int)hr;
	}

}