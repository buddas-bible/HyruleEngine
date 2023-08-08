#include "SphereCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"
#include "AABB.h"

namespace Hyrule
{
	namespace Physics
	{
		SphereCollider::SphereCollider(Object* _obj, COLLIDER_INFO* _info) noexcept :
			Collider(_obj)
		{
			_obj->colliders.push_back(this);
			SetSize(_info->colliderSize);
			SetCenter(_info->colliderCenter);
		}

		AABB SphereCollider::GetAABB()
		{
			Vector3D pos{ object->GetPosition() };
			Vector3D scl{ object->GetScale() };

			float max = std::max(std::max(scl.x, scl.y), scl.z);

			return AABB(pos, max * 1.0f);
		}

		Vector3D SphereCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Vector3D pos{ object->GetPosition() };
			Vector3D scl{ object->GetScale() };

			float max = std::max(std::max(scl.x, scl.y), scl.z);

			return _direction * 0.5f * max + pos;
		}

		Face SphereCollider::FindSupportFace(const Vector3D& _direction)
		{
			return Face(
				Vector3D(), 
				Vector3D(), 
				Vector3D(), 
				0, 1, 2
			);
		}

		Matrix3x3 SphereCollider::GetInertiaTensor(float _mass) noexcept
		{
			Vector3D scl{ object->GetScale() };

			float max = std::max(std::max(scl.x, scl.y), scl.z);
			float radius = 0.5f * max;
			float I{ (2.f / 5.f) * _mass * radius * radius };

			return inertia =
			{
				I, 0.f, 0.f,
				0.f, I, 0.f,
				0.f, 0.f, I
			};
		}

		size_t SphereCollider::GetType() noexcept
		{
			return (size_t)ShapeType::SPHERE;
		}
	}
}
