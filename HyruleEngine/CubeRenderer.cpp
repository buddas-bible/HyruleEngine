#include "CubeRenderer.h"

#include "HEntity.h"
#include "HTransform.h"
#include "RENDERABLE_DESC.h"
#include "IRenderable.h"

namespace hyrule
{
	CubeRenderer::CubeRenderer(HEntity* _entity) :
		Renderer(_entity)
	{
		RENDERABLE_DESC desc;
		desc.meshType = CUBE;
		this->meshData = RendererSystem::Instance()->GetRenderableObject(&desc);
	}

	void CubeRenderer::Render()
	{
		this->meshData->SetWorldTransform(this->entity->GetTransform()->GetWorldMatrix());
	}
}
