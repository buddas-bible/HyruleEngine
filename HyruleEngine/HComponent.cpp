#include "HComponent.h"

namespace hyrule
{
	HComponent::HComponent(HEntity* _entity) : 
		entity(_entity), transform(nullptr), tag(nullptr)
	{}

	bool HComponent::CompareTag(const std::string& _tag)
	{
		return entity->GetTag() == _tag;
	}

	HComponent* HComponent::GetComponent(const std::string&)
	{
		return nullptr;
	}
}