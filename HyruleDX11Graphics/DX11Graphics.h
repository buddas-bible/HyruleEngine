#pragma once
#include "IRenderer.h"


// class ID3D11Device5;
// class ID3D11DeviceContext4;
// class IDXGISwapChain4;
class DXDevice;

struct ID3D11RenderTargetView1;
struct ID3D11DepthStencilView;
class DXRenderTarget;

struct ID3D11RasterizerState2;
class DXRasterizerState;

namespace Hyrule
{
	class DX11Graphics : public IRenderer
	{
	public:
		DX11Graphics();
		virtual ~DX11Graphics();

	private:
		int							m_hWnd;
		// unsigned int				m_msaaQuality;

		DXDevice*					m_Device;
		DXRenderTarget*				m_RenderTarget;
		DXRasterizerState*			m_RasterizerState;

	public:
		virtual int Initialize(int _hwnd) override;
		virtual void Finalize() override;
		virtual void Render() override;
		virtual int OnResize() override;

	private:
		/// <summary>
		/// 초기화 함수
		/// </summary>
		/// <returns>RESULT</returns>
		int CreateDeviceAndSwapChain();
		int CreateRenderTargetAndDepthStencil();
		int CreateRasterState();

	private:
		void SetCamera();
	};

	extern "C"
	{
		__declspec(dllexport) IRenderer* CreateRenderer();
		__declspec(dllexport) void ReleaseRenderer(IRenderer*& _renderer);
	}

}