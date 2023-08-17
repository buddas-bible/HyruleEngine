#include "Collider.h"

namespace Hyrule
{
	Collider::Collider(GameObject* _gameObject) noexcept :
		Component(_gameObject), center(), size(1.f, 1.f, 1.f)
	{

	}
}