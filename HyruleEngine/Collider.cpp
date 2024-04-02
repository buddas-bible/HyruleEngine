#include "Collider.h"

namespace Hyrule
{
	Collider::Collider(Entity* _gameObject) :
		Component(_gameObject), center(), size(1.f, 1.f, 1.f)
	{

	}
}