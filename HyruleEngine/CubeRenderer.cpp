#include "CubeRenderer.h"

#include "Entity.h"
#include "Transform.h"
#include "RENDERABLE_DESC.h"
#include "IRenderable.h"

namespace Hyrule
{
	CubeRenderer::CubeRenderer(Entity* _gameObject) : 
		Renderer(_gameObject)
	{
		RENDERABLE_DESC desc;
		desc.meshType = CUBE;
		this->meshData = RendererSystem::Instance()->GetRenderableObject(&desc);
	}

	void CubeRenderer::Render()
	{
		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
	}
}
