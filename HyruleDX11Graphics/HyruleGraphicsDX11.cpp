#include "HyruleGraphicsDX11.h"
// 아마 그래픽스 구현 부

#include "DXDevice.h"
#include "DXRenderTarget.h"
#include "DXRasterizerState.h"
#include "ICamera.h"
#include "DXCamera.h"

#include "ResourceManager.h"
#include "HyruleMath.h"
#include "Vertex.h"

#include "DXEffect.h"
#include "DXInputLayout.h"

#include "Helper.h"


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
		m_device(), m_renderTarget(), m_rasterizerState(),
		m_camera()
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

		hr = CreateEffectAndInputLayout();

		if (FAILED(hr))
		{
			return hr;
		}

		ResourceManager::GetInstance().Initialize(m_device);



#if _DEBUG
		HelerObject::InitHelperObject();
		hr = CreateHelper();

		if (FAILED(hr))
		{
			return hr;
		}
#endif

		return hr;
	}

	void HyruleGraphicsDX11::Finalize()
	{
		
	}

	void HyruleGraphicsDX11::Render()
	{
#if _DEBUG
		m_axis->SetViewProjTM(m_camera->GetViewProjMatrix());
		m_grid->SetViewProjTM(m_camera->GetViewProjMatrix());
#endif

		m_renderTarget->Bind();
		m_renderTarget->Clear();
		
		///
#if _DEBUG
		m_grid->Render();
		m_axis->Render();
#endif

		///

		m_device->Present();
	}

	long HyruleGraphicsDX11::OnResize()
	{
		HRESULT hr = S_OK;

		hr = m_renderTarget->OnResize();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = m_device->SetCamera(m_camera.get());

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
			return (ICamera*)m_camera.get();
		}

		return nullptr;
	}

	long HyruleGraphicsDX11::CreateDeviceAndSwapChain()
	{
		HRESULT hr = S_OK;

		m_device = std::make_shared<DXDevice>((HWND)m_hWnd);

		hr = m_device->CreateDeviceAndSwapChain();

		if (FAILED(hr))
		{
			return hr;
		}

		hr = m_device->SetCamera(m_camera.get());
		
		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	long HyruleGraphicsDX11::CreateRenderTargetAndDepthStencil()
	{
		HRESULT hr = S_OK;

		m_renderTarget = std::make_shared<DXRenderTarget>(m_device);

		hr = m_renderTarget->CreateRenderTargetAndDepthStencil();

		if (FAILED(hr))
		{
			return hr;
		}

		m_renderTarget->Bind();

		return hr;
	}

	long HyruleGraphicsDX11::CreateRasterState()
	{
		HRESULT hr = S_OK;

		m_rasterizerState = std::make_shared<DXRasterizerState>(m_device);

		hr = m_rasterizerState->CreateRasterizerState();

		if (FAILED(hr))
		{
			return hr;
		}

		return hr;
	}

	long HyruleGraphicsDX11::CreateCamera()
	{
		m_camera = std::make_shared<DXCamera>();

		return S_OK;
	}

	long HyruleGraphicsDX11::CreateEffectAndInputLayout()
	{
		Effects::InitAll(m_device);
		InputLayouts::InitAll(m_device);

		return S_OK;
	}

	long HyruleGraphicsDX11::CreateHelper()
	{
		m_axis = new Helper(m_device, m_rasterizerState, HelerObject::axis);

		////////////////////////////////////////////////////////////////////////////////////////

		m_grid = new Helper(m_device, m_rasterizerState, HelerObject::gizmo);

		return S_OK;
	}
}