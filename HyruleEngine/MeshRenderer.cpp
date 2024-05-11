#include "MeshRenderer.h"

#include "HEntity.h"
#include "HTransform.h"
#include "IRenderable.h"

namespace hyrule
{

	MeshRenderer::MeshRenderer(HEntity* _entity) :
		Renderer(_entity)
	{
		// this->meshData = RendererSystem::GetInstance().GetRenderableObject();
	}

	void MeshRenderer::Render()
	{
		this->meshData->SetWorldTransform(this->entity->GetTransform()->GetWorldMatrix());
	}
}