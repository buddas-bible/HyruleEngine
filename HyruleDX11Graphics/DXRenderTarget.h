#pragma once
#include "framework.h"

struct ID3D11RenderTargetView1;
struct ID3D11DepthStencilView;

namespace hyrule
{
	class DXDevice;

	class DXRenderTarget
	{
	public:
		DXRenderTarget(std::shared_ptr<DXDevice>);
		~DXRenderTarget();

	private:
		template <typename T>
		using Comptr = Microsoft::WRL::ComPtr<T>;

		std::shared_ptr<DXDevice> m_device;
		// std::weak_ptr<DXDevice> m_dxDevice;

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
	};
}