#pragma once
#include "IRenderer.h"


class IUnknown;
class ID3D11Device;
class ID3D11DeviceContext;
class IDXGISwapChain;
class ID3D11Texture2D;
class ID3D11RenderTargetView;
class ID3D11RasterizerState;
class ID3D11DepthStencilView;


namespace Hyrule
{
	class DX11Graphics : public IRenderer
	{
	public:
		DX11Graphics() = default;
		virtual ~DX11Graphics();

	private:
		int m_hWnd;

		ID3D11Device*			device;
		ID3D11DeviceContext*	deviceContext;
		IDXGISwapChain*			swapChain;

		ID3D11Texture2D*		backBuffer;
		ID3D11RenderTargetView*	renderTargetView;

		ID3D11Texture2D*		depthStencil;
		ID3D11DepthStencilView* depthStencilView;

		ID3D11RasterizerState* currRasterizerState;			// 현재 레스터 상태
		ID3D11RasterizerState* solidRasterizerState;			// 채우는 레스터 상태
		ID3D11RasterizerState* wireRasterizerState;

	public:
		virtual int Initialize(int _hwnd) override;
		virtual void Finalize() override;
		virtual void Update() override;
		virtual void Render() override;
		
		virtual int OnResize() override;

		void SetCamera();

	private:
		template <class T>
		void Release(T* ptr)
		{
			if (ptr == nullptr)
			{
				return;
			}

			ptr->Release();
			ptr = nullptr;
		}

	private:
		int CreateDevice();
		int CreateSwapChain();
		int CreateRenderTargetView();
		int CreateDepthStencilView();
		int CreateRasterState();
	};
}