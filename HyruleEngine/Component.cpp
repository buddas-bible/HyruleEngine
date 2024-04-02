#include "Component.h"

namespace Hyrule
{
	Component::Component(Entity* _gameObject) : 
		gameObject(_gameObject), transform(nullptr), tag(nullptr)
	{}

	bool Component::CompareTag(const std::string&)
	{
		return gameObject->GetTag();
	}

	Component* Component::GetComponent(const std::string&)
	{
		return nullptr;
	}
}