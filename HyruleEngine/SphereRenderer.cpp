#include "SphereRenderer.h"

#include "Entity.h"
#include "Transform.h"
#include "RENDERABLE_DESC.h"
#include "IRenderable.h"

namespace Hyrule
{
	SphereRenderer::SphereRenderer(Entity* _gameObject) :
		Renderer(_gameObject)
	{
		RENDERABLE_DESC desc;
		desc.meshType = SPHERE;
		this->meshData = RendererSystem::Instance()->GetRenderableObject(&desc);
	}

	void SphereRenderer::Render()
	{
		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
	}
}