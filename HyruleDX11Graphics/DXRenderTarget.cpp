#include "DXRenderTarget.h"
#include "framework.h"
#include "DXDevice.h"

DXRenderTarget::DXRenderTarget(DXDevice* _device)
	: m_dxDevice(_device), 
	m_renderTargetView(), m_depthStencilView()
{

}

DXRenderTarget::~DXRenderTarget()
{
	Release(m_renderTargetView);
	Release(m_depthStencilView);
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

void DXRenderTarget::OnResize()
{
	m_dxDevice->GetSwapChain()->ResizeBuffers(
		NULL,
		NULL,
		NULL,
		DXGI_FORMAT_UNKNOWN,
		0
	);

	CreateRenderTargetAndDepthStencil();
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
	ZeroMemory(&backBuffer, sizeof(D3D11_TEXTURE2D_DESC));
	backBuffer->GetDesc(&bufferDesc);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX;
	viewport.TopLeftY;
	viewport.Width;
	viewport.Height;
	viewport.MaxDepth;
	viewport.MinDepth;

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

	return (int)hr;
}
