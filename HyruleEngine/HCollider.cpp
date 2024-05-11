#include "HCollider.h"

namespace hyrule
{
	HCollider::HCollider(HEntity* _gameObject) :
		HComponent(_gameObject), center(), size(1.f, 1.f, 1.f)
	{

	}
}