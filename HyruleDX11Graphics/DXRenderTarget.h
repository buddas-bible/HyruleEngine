#pragma once

class DXDevice;
struct ID3D11RenderTargetView1;
struct ID3D11DepthStencilView;

class DXRenderTarget
{
public:
	DXRenderTarget(DXDevice* _device);
	~DXRenderTarget();

private:
	DXDevice* m_dxDevice;

	ID3D11RenderTargetView1* m_renderTargetView;
	ID3D11DepthStencilView* m_depthStencilView;

public:
	int CreateRenderTargetAndDepthStencil();

	void OnResize();

private:
	int CreateRenderTarget();
	int CreateDepthStencil();
};

