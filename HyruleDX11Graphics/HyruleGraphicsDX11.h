#pragma once
#include "framework.h"

#include "IGraphics.h"


namespace Hyrule
{
	class DXDevice;
	class DXRenderTarget;
	class DXRasterizerState;
	class DXCamera;

	class HyruleGraphicsDX11 : public IGraphics
	{
	public:
		HyruleGraphicsDX11();
		virtual ~HyruleGraphicsDX11();

	private:
		int							m_hWnd;
		// unsigned int				m_msaaQuality;

		DXDevice*					m_Device;
		DXRenderTarget*				m_RenderTarget;
		DXRasterizerState*			m_RasterizerState;
		DXCamera*					m_camera;

	public:
		virtual long Initialize(int _hwnd) override;
		virtual void Finalize() override;
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
	};

	extern "C"
	{
		__declspec(dllexport) IGraphics* CreateRenderer();
	}
}