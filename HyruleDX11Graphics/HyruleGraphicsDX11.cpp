#include "HyruleGraphicsDX11.h"
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


namespace hyrule
{
	extern "C"
	{
		__declspec(dllexport) IGraphics* CreateRenderer()
		{
			auto instance = new HyruleGraphicsDX11;

			g_renderer = instance;

			return instance;
		}
	}

	HyruleGraphicsDX11::HyruleGraphicsDX11()
		: m_hWnd(),
		m_device(), m_renderTarget(), m_rasterizerState(),
		m_camera()
	{}


	std::shared_ptr<hyrule::DXDevice> HyruleGraphicsDX11::Device()
	{
		return m_device;
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

		HelerObject::InitHelperObject();
		hr = CreateHelper();

		if (FAILED(hr))
		{
			return hr;
		}
#if _DEBUG
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
		m_axis->SetViewProjTM(m_camera->GetViewProjMatrix());
		m_gizmo->SetViewProjTM(m_camera->GetViewProjMatrix());
#if _DEBUG
#endif

		ObjectManager::GetInstance().Update(m_camera->GetViewProjMatrix());

	}

	void HyruleGraphicsDX11::Render()
	{

		m_renderTarget->Bind();
		m_renderTarget->Clear();
		
		///
		m_gizmo->Render();
		m_axis->Render();
#if _DEBUG
#endif

		ObjectManager::GetInstance().Render(m_camera->GetPosition());

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

	void HyruleGraphicsDX11::DrawLine(const Vector3D& _vec0, const Vector3D& _vec1)
	{
		auto device = g_renderer->Device();

		device->GetDeviceContext()->RSSetState(0);
		device->GetDeviceContext()->IASetInputLayout(InputLayouts::PCLayout->GetInputLayout());
		device->GetDeviceContext()->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

		PC verties[]
		{
			Vector3{ _vec0.x ,_vec0.y, _vec0.z}, Vector4{DXColor::CadetBlue},
			Vector3{ _vec1.x, _vec1.y, _vec1.z}, Vector4{DXColor::CadetBlue},
		};

		UINT indies[]
		{
			0, 1,
		};

		auto line = ResourceManager::GetInstance().CreateMesh(
			&verties, sizeof(verties),
			&indies, sizeof(indies),
			ARRAYSIZE(indies)
		);

		UINT stride = sizeof(PC);
		UINT offset = 0;
		device->GetDeviceContext()->IASetVertexBuffers(
			0,
			1,
			line->vertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);

		device->GetDeviceContext()->IASetIndexBuffer(
			line->indexBuffer.Get(),
			DXGI_FORMAT_R32_UINT,					// 32비트 unsigned int 형으로 읽음
			0
		);

		Matrix4x4 _worldViewProj{ ViewProj()};
		Effects::PCEffect->SetWorldViewProj(_worldViewProj);

		D3DX11_TECHNIQUE_DESC techDesc;
		Effects::PCEffect->GetTechnique()->GetDesc(&techDesc);

		for (UINT p = 0; p < techDesc.Passes; ++p)
		{
			Effects::PCEffect->GetTechnique()->GetPassByIndex(p)->Apply(0, device->GetDeviceContext());

			device->GetDeviceContext()->DrawIndexed(line->indexCount, 0, 0);
		}

		delete line;
	}

	void HyruleGraphicsDX11::DrawSphere(const Vector3D& _pos)
	{

	}

	hyrule::Matrix4x4 HyruleGraphicsDX11::ViewProj()
	{
		return g_renderer->GetCamera()->GetViewProjMatrix();
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

		ObjectManager::GetInstance().AddObject(newObject);
		return newObject;
	}
}