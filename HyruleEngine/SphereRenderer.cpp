#include "SphereRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "RENDERABLE_DESC.h"
#include "IRenderable.h"

namespace Hyrule
{
	SphereRenderer::SphereRenderer(GameObject* _gameObject) noexcept :
		Renderer(_gameObject)
	{
		RENDERABLE_DESC desc;
		desc.meshType = SPHERE;
		this->meshData = RendererSystem::GetInstance().GetRenderableObject(&desc);
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