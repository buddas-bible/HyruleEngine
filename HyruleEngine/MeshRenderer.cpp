#include "MeshRenderer.h"

#include "GameObject.h"
#include "Transform.h"
#include "IRenderable.h"

namespace Hyrule
{

	MeshRenderer::MeshRenderer(GameObject* _gameObject) noexcept :
		Renderer(_gameObject)
	{
		// this->meshData = RendererSystem::GetInstance().GetRenderableObject();
	}

// 	void MeshRenderer::FixedUpdate()
// 	{
// 
// 	}
// 
	void MeshRenderer::Update()
	{
		this->meshData->SetWorldTransform(this->gameObject->GetTransform()->GetWorldMatrix());
	}

	// 	void MeshRenderer::LastUpdate()
	// 	{
	// 
	// 	}
	// 
	// 	void MeshRenderer::Render()
	// 	{
	// 	}
}