#include "SphereRenderer.h"

#include "GameObject.h"
#include "Transform.h"

namespace Hyrule
{
	SphereRenderer::SphereRenderer(GameObject* _gameObject) noexcept :
		Renderer(_gameObject)
	{
		this->meshData = RendererSystem::GetInstance().GetRenderableObject();
	}

// 	void SphereRenderer::FixedUpdate()
// 	{
// 
// 	}

	void SphereRenderer::Update()
	{
		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
	}

	// 	void SphereRenderer::LastUpdate()
	// 	{
	// 
	// 	}
	// 
	// 	void SphereRenderer::Render()
	// 	{
	// 		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
	// 	}
}