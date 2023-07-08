#pragma once
#include "framework.h"

struct ID3D11RenderTargetView1;
struct ID3D11DepthStencilView;

namespace Hyrule
{
	class DXDevice;

	class DXRenderTarget
	{
	public:
		DXRenderTarget(DXDevice* _device);
		~DXRenderTarget();

	private:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		DXDevice* m_dxDevice;

		Comptr<ID3D11RenderTargetView1> m_renderTargetView;
		Comptr<ID3D11DepthStencilView> m_depthStencilView;

	public:
		long CreateRenderTargetAndDepthStencil();
		long OnResize();

		void Clear();

		void Bind();

	private:
		long CreateRenderTarget();
		long CreateDepthStencil();

		void ReleaseAll();
	};
}