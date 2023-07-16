#include "PlaneCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		PlaneCollider::PlaneCollider(COLLIDER_INFO* _info) noexcept
		{
			this->SetSize(_info->colliderSize);
			this->SetCenter(_info->colliderCenter);
		}

		Vector3D PlaneCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Matrix4x4 world = object->GetWorldTM();

			return Vector3D();
		}

		Face PlaneCollider::FindSupportFace(const Vector3D&)
		{
			return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
		}
	}
}