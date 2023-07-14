#include "ConvexCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"

namespace Hyrule
{
	namespace Physics
	{
		ConvexCollider::ConvexCollider(COLLIDER_INFO* _info) noexcept
		{
			SetSize(_info->colliderSize);
			SetCenter(_info->colliderCenter);
		}

		Vector3D ConvexCollider::FindFarthestPoint(const Vector3D&)
		{
			Matrix4x4 world = object->GetWorldTM();
			return Vector3D();
		}
	}
}