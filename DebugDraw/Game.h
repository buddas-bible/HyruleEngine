#pragma once
#include "../DXTK/inc/PrimitiveBatch.h"
#include "../DXTK/inc/VertexTypes.h"
#include "../DXTK/inc/CommonStates.h"
#include "../DXTK/inc/Effects.h"
#include "../DXTK/inc/DirectXHelpers.h"

#include <wrl.h>
#include <memory>
#include <DirectXMath.h>


class Game
{
	using VertexType = DirectX::VertexPositionColor;

	std::unique_ptr<DirectX::CommonStates> m_states;
	std::unique_ptr<DirectX::BasicEffect> m_effect;
	std::unique_ptr<DirectX::PrimitiveBatch<VertexType>> m_batch;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

	void CreateDeviceDependentResources();
	void OnDeviceLost();
	void Render();
};

