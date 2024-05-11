#include "SphereRenderer.h"

#include "HEntity.h"
#include "HTransform.h"
#include "RENDERABLE_DESC.h"
#include "IRenderable.h"

namespace hyrule
{
	SphereRenderer::SphereRenderer(HEntity* _entity) :
		Renderer(_entity)
	{
		RENDERABLE_DESC desc;
		desc.meshType = SPHERE;
		this->meshData = RendererSystem::Instance()->GetRenderableObject(&desc);
	}

	void SphereRenderer::Render()
	{
		this->meshData->SetWorldTransform(this->entity->GetTransform()->GetWorldMatrix());
	}
}