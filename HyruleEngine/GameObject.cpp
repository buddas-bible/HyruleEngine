#include "GameObject.h"

#include "Transform.h"

namespace Hyrule
{
	GameObject::GameObject() :
		tag(), name(),
		components(), transform()
	{
		// 게임 오브젝트는 트랜스폼을 가지고 태어남
		this->transform = this->AddComponent<Transform>();
	}

	GameObject::GameObject(const std::wstring& _name, Scene* _scene) :
		name(_name), scene(_scene)
	{

	}

	GameObject::~GameObject()
	{
		for (auto& e : components)
		{
			e->OnDestroy();
			delete e;
		}

		// 벡터는 알아서 사라질테니까 따로 클리어 안함.
	}

	const std::wstring& GameObject::GetName()
	{
		return this->name;
	}

	void GameObject::SetName(const std::wstring& _name)
	{
		this->name = _name;
	}

	const std::wstring& GameObject::GetTag()
	{
		return this->tag;
	}

	void GameObject::SetTag(const std::wstring& _tag)
	{
		this->tag = _tag;
	}

	Scene* GameObject::GetScene()
	{
		return scene;
	}
}