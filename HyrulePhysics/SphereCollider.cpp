#include "SphereCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		SphereCollider::SphereCollider(Object* _obj, COLLIDER_INFO* _info) noexcept :
			Collider(_obj)
		{
			SetSize(_info->colliderSize);
			SetCenter(_info->colliderCenter);
			type = ColliderType::SPHERE;
		}

		Vector3D SphereCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Vector3D pos{ object->GetPosition() };
			Vector3D scl{ object->GetScale() };

			float max = std::max(std::max(scl.x, scl.y), scl.z);

			return _direction * 0.5f * max + pos;
		}

		Face SphereCollider::FindSupportFace(const Vector3D&)
		{
			return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
		}

		Matrix3x3 SphereCollider::GetInertiaTensor(float) noexcept
		{
			return inertia =
			{
				1.f, 0.f, 0.f,
				0.f, 1.f, 0.f,
				0.f, 0.f, 1.f
			};
		}
	}
}
