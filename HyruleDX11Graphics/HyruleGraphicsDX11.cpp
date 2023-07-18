﻿#include "HyruleGraphicsDX11.h"
// 아마 그래픽스 구현 부

#include "DXDevice.h"
#include "DXRenderTarget.h"
#include "DXRasterizerState.h"
#include "ICamera.h"
#include "DXCamera.h"

#include "ResourceManager.h"
#include "ObjectManager.h"
#include "HyruleMath.h"
#include "Vertex.h"

#include "DXEffect.h"
#include "DXInputLayout.h"

#include "Helper.h"
#include "Renderable_desc.h"


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
	{}


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
		if (m_axis)
		{
			delete m_axis;
			m_axis = nullptr;
		}

		if (m_gizmo)
		{
			delete m_gizmo;
			m_gizmo = nullptr;
		}
	}

	void HyruleGraphicsDX11::Update()
	{
#if _DEBUG
		m_axis->SetViewProjTM(m_camera->GetViewProjMatrix());
		m_gizmo->SetViewProjTM(m_camera->GetViewProjMatrix());
#endif

		ObjectManager::GetInstance().Update(m_camera->GetViewProjMatrix());

	}

	void HyruleGraphicsDX11::Render()
	{

		m_renderTarget->Bind();
		m_renderTarget->Clear();
		
		///
#if _DEBUG
		m_gizmo->Render();
		m_axis->Render();
#endif

		ObjectManager::GetInstance().Render();
		ObjectManager::GetInstance().Render();

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

		m_gizmo = new Helper(m_device, m_rasterizerState, HelerObject::gizmo);

		return S_OK;
	}

	IRenderable* HyruleGraphicsDX11::GetRenderableObject(RENDERABLE_DESC* _desc)
	{
		RenderableObject* newObject = nullptr;

		switch (_desc->meshType)
		{
			case CUBE:
			{
				newObject = new RenderableObject(m_device, m_rasterizerState, HelerObject::cube);
			}
			break;

			case PLANE:
			{
				newObject = new RenderableObject(m_device, m_rasterizerState, HelerObject::plane);
			}
			break;

			case SPHERE:
			{
				newObject = new RenderableObject(m_device, m_rasterizerState, HelerObject::sphere);
			}
			break;

			case CAPSULE:
			{
				// auto newObject = new RenderableObject(m_device, m_rasterizerState, HelerObject::cube);
				// renderableList.push_back(newObject);
			}
			break;

			default:
			{
				auto mesh = ResourceManager::GetInstance().GetMesh(_desc->meshName);
				newObject = new RenderableObject(m_device, m_rasterizerState, mesh);
			}
			break;
		}

		return newObject;
	}
}