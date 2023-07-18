#include "CubeRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "RENDERABLE_DESC.h"
#include "IRenderable.h"

namespace Hyrule
{
	CubeRenderer::CubeRenderer(GameObject* _gameObject) noexcept : 
		Renderer(_gameObject)
	{
		RENDERABLE_DESC desc;
		desc.meshType = CUBE;
		this->meshData = RendererSystem::GetInstance().GetRenderableObject(&desc);
	}

// 	void BoxRenderer::FixedUpdate()
// 	{
// 
// 	}

	void CubeRenderer::Update()
	{
		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
	}

// 	void BoxRenderer::LastUpdate()
// 	{
// 
// 	}

// 	void BoxRenderer::Render()
// 	{
// 		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
// 	}
}
