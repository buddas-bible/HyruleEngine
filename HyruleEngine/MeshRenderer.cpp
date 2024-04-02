#include "MeshRenderer.h"

#include "Entity.h"
#include "Transform.h"
#include "IRenderable.h"

namespace Hyrule
{

	MeshRenderer::MeshRenderer(Entity* _gameObject) :
		Renderer(_gameObject)
	{
		// this->meshData = RendererSystem::GetInstance().GetRenderableObject();
	}

	void MeshRenderer::Render()
	{
		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
	}
}