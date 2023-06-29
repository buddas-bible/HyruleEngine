#include "DXRenderTarget.h"

#include "framework.h"
#include "DXDevice.h"

namespace Hyrule
{

	DXRenderTarget::DXRenderTarget(DXDevice* _device)
		: m_dxDevice(_device),
		m_renderTargetView(), m_depthStencilView()
	{

	}

	DXRenderTarget::~DXRenderTarget()
	{
		ReleaseAll();
	}

	int DXRenderTarget::CreateRenderTargetAndDepthStencil()
	{
		HRESULT hr = S_OK;

		hr = CreateRenderTarget();

		if (FAILED(hr))
		{
			return (int)hr;
		}

		hr = CreateDepthStencil();

		if (FAILED(hr))
		{
			return (int)hr;
		}

		return (int)hr;
	}

	int DXRenderTarget::OnResize()
	{
		HRESULT hr = S_OK;

		ReleaseAll();

		hr = m_dxDevice->GetSwapChain()->ResizeBuffers(
			NULL,
			NULL,
			NULL,
			DXGI_FORMAT_UNKNOWN,
			0
		);

		if (FAILED(hr))
		{
			return (int)hr;
		}

		hr = m_dxDevice->SetViewport();

		if (FAILED(hr))
		{
			return (int)hr;
		}

		hr = CreateRenderTargetAndDepthStencil();

		if (FAILED(hr))
		{
			return (int)hr;
		}

		return (int)hr;
	}

	void DXRenderTarget::Clear()
	{
		m_dxDevice->GetDeviceContext()->ClearRenderTargetView(
			m_renderTargetView,
			DXColor::Bisque
		);

		m_dxDevice->GetDeviceContext()->ClearDepthStencilView(
			m_depthStencilView,
			D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
			1.0f,
			0
		);
	}

	/// <summary>
	/// 렌더 타켓을 파이프 라인에 바인딩 함.
	/// </summary>
	void DXRenderTarget::Bind()
	{
		// m_dxDevice->GetDeviceContext()->OMSetRenderTargets(
		// 	1,
		// 	&(ID3D11RenderTargetView*)m_renderTargetView,
		// 	m_depthStencilView
		// );
		ID3D11RenderTargetView* ppRenderTargetViews[] = { m_renderTargetView };

		m_dxDevice->GetDeviceContext()->OMSetRenderTargets(
			1,
			ppRenderTargetViews,
			m_depthStencilView
		);
	}

	int DXRenderTarget::CreateRenderTarget()
	{
		HRESULT hr = S_OK;

		ID3D11Texture2D* backBuffer;
		hr = m_dxDevice->GetSwapChain()->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(void**)&backBuffer
		);

		if (FAILED(hr))
		{
			return (int)hr;
		}

		hr = m_dxDevice->GetDevice()->CreateRenderTargetView1(
			backBuffer,
			nullptr,
			&m_renderTargetView
		);

		if (FAILED(hr))
		{
			return (int)hr;
		}

		D3D11_TEXTURE2D_DESC bufferDesc;
		ZeroMemory(&bufferDesc, sizeof(D3D11_TEXTURE2D_DESC));
		backBuffer->GetDesc(&bufferDesc);

		Release(backBuffer);

		return (int)hr;
	}

	int DXRenderTarget::CreateDepthStencil()
	{
		HRESULT hr = S_OK;

		ID3D11Texture2D* backBuffer;
		hr = m_dxDevice->GetSwapChain()->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			(void**)&backBuffer
		);

		D3D11_TEXTURE2D_DESC backBufferDesc{};
		ZeroMemory(&backBufferDesc, sizeof(backBufferDesc));
		backBuffer->GetDesc(&backBufferDesc);

		if (FAILED(hr))
		{
			return (int)hr;
		}

		D3D11_TEXTURE2D_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.Width = backBufferDesc.Width;
		depthStencilDesc.Height = backBufferDesc.Height;
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		ID3D11Texture2D* depthStencil;
		hr = m_dxDevice->GetDevice()->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&depthStencil
		);

		if (FAILED(hr))
		{
			return (int)hr;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
		ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
		depthStencilViewDesc.Format = depthStencilDesc.Format;
		depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		depthStencilViewDesc.Flags = 0;
		depthStencilViewDesc.Texture2D.MipSlice = 0;

		hr = m_dxDevice->GetDevice()->CreateDepthStencilView(
			depthStencil,
			&depthStencilViewDesc,
			&m_depthStencilView
		);

		if (FAILED(hr))
		{
			return (int)hr;
		}

		Release(backBuffer);
		Release(depthStencil);

		return (int)hr;
	}

	void DXRenderTarget::ReleaseAll()
	{
		Release(m_depthStencilView);
		Release(m_renderTargetView);
	}

}