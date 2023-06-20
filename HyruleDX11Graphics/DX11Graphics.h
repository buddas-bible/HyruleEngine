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
		DX11Graphics() = default;
		virtual ~DX11Graphics();

	private:
		int							m_hWnd;
		// unsigned int				m_msaaQuality;

		/// <summary>
		/// 이 세 개를 하나로 묶음
		/// </summary>
		// ID3D11Device5*			m_device;
		// ID3D11DeviceContext4*	m_deviceContext;
		// IDXGISwapChain4*			m_swapChain;		
		DXDevice*					m_Device;

		/// </summary>
		/// 이 두 개를 하나로 묶음
		/// </summary>
		// ID3D11RenderTargetView1*	m_renderTargetView;
		// ID3D11DepthStencilView*	m_depthStencilView;
		DXRenderTarget*				m_RenderTarget;

		/// <summary>
		/// 이 세 개를 하나로 묶음
		/// </summary>
		// ID3D11RasterizerState2*	m_currRasterizerState;			// 현재 레스터 상태
		// ID3D11RasterizerState2*	m_solidRasterizerState;			// 채우는 레스터 상태
		// ID3D11RasterizerState2*	m_wireRasterizerState;
		DXRasterizerState*			m_RasterizerState;

	public:
		virtual int Initialize(int _hwnd) override;
		virtual void Finalize() override;
		virtual void Update() override;
		virtual void Render() override;
		
		virtual int OnResize() override;

		void SetCamera();

	private:
		int CreateDeviceAndSwapChain();
		int CreateRenderTargetAndDepthStencil();
		// int CreateDevice();
		// int CreateSwapChain();
		// int CreateRenderTargetView();
		// int CreateDepthStencilView();
		int CreateRasterState();
	};
}