#include "Renderer.h"

#include "IRenderable.h"

namespace Hyrule
{
	Renderer::Renderer(GameObject* _gameObject) noexcept :
		Component(_gameObject), meshData()
	{

	}

	void Renderer::OnEnable()
	{
		meshData->OnEnble();
	}

	void Renderer::OnDisable()
	{
		meshData->OnDisable();
	}
}