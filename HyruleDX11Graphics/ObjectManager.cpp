#include "ObjectManager.h"

#include "RenderableObject.h"
#include "HyruleMath.h"

namespace Hyrule
{
	ObjectManager& ObjectManager::GetInstance()
	{
		static ObjectManager instance;

		return instance;
	}

	Hyrule::RenderableObject* ObjectManager::CreateObject()
	{
		return nullptr;
	}

	std::vector<RenderableObject*>& ObjectManager::GetRenderableObjects()
	{
		return this->renderableList;
	}

	void ObjectManager::AddObject(RenderableObject* _obj)
	{
		renderableList.push_back(_obj);
	}

	void ObjectManager::Update(const Matrix4x4& _viewProj)
	{
		for (auto& e : renderableList)
		{
			if (e->isActive())
			{
				e->SetViewProjTM(_viewProj);
			}
		}
	}

	void ObjectManager::Render()
	{
		for (auto& e : renderableList)
		{
			if (e->isActive())
			{
				e->Render();
			}
		}
	}

	// void ObjectManager::DisableObject(RenderableObject* _object)
	// {
	// 	if (_object == nullptr)
	// 	{
	// 		return;
	// 	}
	// 
	// 	auto itr = std::find(activatedObject.begin(), activatedObject.end(), _object);
	// 
	// 	if (itr != activatedObject.end())
	// 	{
	// 		activatedObject.erase(itr);
	// 	}
	// }
	// 
	// void ObjectManager::EnableObject(RenderableObject* _object)
	// {
	// 	auto itr = std::find(activatedObject.begin(), activatedObject.end(), _object);
	// 
	// 	if (itr == activatedObject.end())
	// 	{
	// 		activatedObject.push_back(_object);
	// 	}
	// }
}