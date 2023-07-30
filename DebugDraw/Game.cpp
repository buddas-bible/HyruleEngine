#include "Game.h"
#include "../DXTK/inc/SimpleMath.h"

using namespace DirectX;

void Game::CreateDeviceDependentResources()
{
	m_states = std::make_unique<DirectX::CommonStates>(device);

	m_effect = std::make_unique<BasicEffect>(device);
	m_effect->SetVertexColorEnabled(true);

	DX::ThrowIfFailed(
		CreateInputLayoutFromEffect<VertexType>(device, m_effect.get(),
			m_inputLayout.ReleaseAndGetAddressOf())
	);

	auto context = m_deviceResources->GetD3DDeviceContext();
	m_batch = std::make_unique<PrimitiveBatch<VertexType>>(context);
}

void Game::OnDeviceLost()
{
	m_states.reset();
	m_effect.reset();
	m_batch.reset();
	m_inputLayout.Reset();
}

void Game::Render()
{
	context->OMSetBlendState(m_states->Opaque(), nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(m_states->DepthNone(), 0);
	context->RSSetState(m_states->CullNone());

	m_effect->Apply(context);

	context->IASetInputLayout(m_inputLayout.Get());

	m_batch->Begin();

	VertexPositionColor v1(SimpleMath::Vector3(0.f, 0.5f, 0.5f), DirectX::Colors::Yellow);
	VertexPositionColor v2(SimpleMath::Vector3(0.5f, -0.5f, 0.5f), DirectX::Colors::Yellow);
	VertexPositionColor v3(SimpleMath::Vector3(-0.5f, -0.5f, 0.5f), DirectX::Colors::Yellow);

	m_batch->DrawTriangle(v1, v2, v3);

	m_batch->End();
}
