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
		// m_axis->SetViewProjTM(m_camera->GetViewProjMatrix());
		m_grid->SetViewProjTM(m_camera->GetViewProjMatrix());


		m_renderTarget->Clear();
		
		///
		// m_axis->Render();
		 m_grid->Render();

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
		// PC axis[] =
		// {
		// 	{Vector3D(0.f, 0.01f, 0.f), Vector4D(DXColor::Red),},
		// 	{Vector3D(15.f, 0.01f, 0.f), Vector4D(DXColor::Red),},
		// 
		// 	{Vector3D(0.f, 0.f, 0.f),	Vector4D(DXColor::Green),},
		// 	{Vector3D(0.f ,15.f, 0.f), Vector4D(DXColor::Green),},
		// 
		// 	{Vector3D(0.f, 0.01f, 0.f),	Vector4D(DXColor::Blue),},
		// 	{Vector3D(0.f ,0.01f, 15.f), Vector4D(DXColor::Blue),},
		// };
		// 
		// UINT indices[] = {
		// 	0, 1,			// x
		// 	2, 3,			// y
		// 	4, 5,			// z
		// };
		// 
		// auto axisMesh = ResourceManager::GetInstance().AddMesh(
		// 	L"Axis",
		// 	axis, sizeof(axis),
		// 	indices, sizeof(indices),
		// 	ARRAYSIZE(indices)
		// );
		// 
		// m_axis = new Helper(m_device, m_rasterizerState, axisMesh);

		////////////////////////////////////////////////////////////////////////////////////////

		PC vertices[100];
		for (int i = 0; i < 100; i++)
		{
			vertices[i].pos = Vector3D((i % 10) - 5.0f, 0.0f, (float)(i / 10) - 5.0f);
			vertices[i].color = Vector4D(DXColor::White);
		}

		UINT index[40];
		for (int i = 0; i < 10; i++)
		{
			index[i * 2] = i;
			index[i * 2 + 1] = i + 90;
		}

		for (int i = 0; i < 10; i++)
		{
			index[20 + (i * 2)] = i * 10;
			index[20 + (i * 2) + 1] = i * 10 + 9;
		}

		auto gridMesh = ResourceManager::GetInstance().AddMesh(
			L"Grid",
			vertices, sizeof(vertices),
			index, sizeof(index),
			ARRAYSIZE(index)
		);

		m_grid = new Helper(m_device, m_rasterizerState, gridMesh);

		return S_OK;
	}
}