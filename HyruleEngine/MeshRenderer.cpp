#include "MeshRenderer.h"


namespace Hyrule
{

	MeshRenderer::MeshRenderer(GameObject* _gameObject) noexcept :
		Component(_gameObject),
		meshData()
	{

	}

	MeshRenderer::~MeshRenderer() noexcept
	{

	}

}