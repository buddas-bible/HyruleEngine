#include "CubeRenderer.h"

#include "GameObject.h"
#include "Transform.h"

namespace Hyrule
{
	CubeRenderer::CubeRenderer(GameObject* _gameObject) noexcept : 
		Renderer(_gameObject)
	{
		this->meshData = RendererSystem::GetInstance().GetRenderableObject();
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
