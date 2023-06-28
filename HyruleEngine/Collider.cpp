#include "Collider.h"

namespace Hyrule
{
	Collider::Collider(GameObject* _gameObject) noexcept :
		Component(_gameObject),
		collided(), colliderList()
	{

	}

	bool Collider::IsColliding()
	{
		return this->collided;
	}

}