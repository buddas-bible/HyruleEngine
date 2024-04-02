#include "Renderer.h"

#include "IRenderable.h"

namespace Hyrule
{
	Renderer::Renderer(Entity* _gameObject) :
		Component(_gameObject), meshData()
	{}

//	void Renderer::OnEnable()
//	{
//		meshData->OnEnble();
//	}
//
//	void Renderer::OnDisable()
//	{
//		meshData->OnDisable();
//	}
//
//#if _DEBUG
//	void Renderer::OnCollisionEnter()
//	{
//		meshData->OnCollisionEnter();
//	}
//
//	void Renderer::OnCollisionStay()
//	{
//		meshData->OnCollisionStay();
//	}
//
//	void Renderer::OnCollisionExit()
//	{
//		meshData->OnCollisionExit();
//	}
//#endif
}