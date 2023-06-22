#include "GameObject.h"


namespace Hyrule
{
	Hyrule::GameObject* GameObject::GetParent()
	{
		return parent;
	}

	void GameObject::SetParent(GameObject* _gameObject)
	{
		parent = _gameObject;
	}
}