#include "Renderer.h"

#include "IRenderable.h"

namespace Hyrule
{
	Renderer::Renderer(GameObject* _gameObject) noexcept :
		Component(_gameObject), meshData()
	{}

	void Renderer::OnEnable()
	{
		meshData->OnEnble();
	}

	void Renderer::OnDisable()
	{
		meshData->OnDisable();
	}

	void Renderer::OnCollisionEnter()
	{
#if _DEBUG
		meshData->OnCollisionEnter();
#endif
	}

	void Renderer::OnCollisionStay()
	{
#if _DEBUG
		meshData->OnCollisionStay();
#endif
	}

	void Renderer::OnCollisionExit()
	{
#if _DEBUG
		meshData->OnCollisionExit();
#endif
	}
}