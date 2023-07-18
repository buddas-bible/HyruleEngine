#pragma once
#include "framework.h"
#include <memory>
#include <vector>
#include "IGraphics.h"
#include "RenderableObject.h"

namespace Hyrule
{
	class DXDevice;
	class DXRenderTarget;
	class DXRasterizerState;
	class DXCamera;
	class ICamera;

	class RenderableObject;
	struct RENDERABLE_DESC;

	class Helper;

	class HyruleGraphicsDX11 : public IGraphics
	{
	public:
		HyruleGraphicsDX11();
		virtual ~HyruleGraphicsDX11() = default;

	private:
		int							m_hWnd;
		// unsigned int				m_msaaQuality;

		std::shared_ptr<DXDevice>	m_device;
		std::shared_ptr<DXRenderTarget>	m_renderTarget;
		std::shared_ptr<DXRasterizerState>	m_rasterizerState;

		std::shared_ptr<DXCamera>	m_camera;

	public:
		virtual long Initialize(int _hwnd) override;
		virtual void Finalize() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual long OnResize() override;
		ICamera* GetCamera();

	private:
		/// <summary>
		/// 초기화 함수
		/// </summary>
		/// <returns>RESULT</returns>
		long CreateDeviceAndSwapChain();
		long CreateRenderTargetAndDepthStencil();
		long CreateRasterState();
		long CreateCamera();
		long CreateEffectAndInputLayout();

#if _DEBUG
		long CreateHelper();

		virtual IRenderable* GetRenderableObject(RENDERABLE_DESC*) override;
		std::vector<RenderableObject*> renderableList;
		std::vector<RenderableObject*> disableList;
		std::vector<RenderableObject*> enableList;

		Helper* m_axis;
		Helper* m_gizmo;
#endif
	};

	extern "C"
	{
		__declspec(dllexport) IGraphics* CreateRenderer();
	}
}