#include "MeshRenderer.h"


namespace Hyrule
{

	MeshRenderer::MeshRenderer(GameObject* _gameObject) noexcept :
		Renderer(_gameObject),
		meshData()
	{

	}

	MeshRenderer::~MeshRenderer() noexcept
	{

	}

}