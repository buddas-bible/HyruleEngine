#include "SphereCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"
#include "AABB.h"

namespace Hyrule
{
	namespace Physics
	{
		SphereCollider::SphereCollider(Object* _obj, COLLIDER_INFO* _info) :
			Collider(_obj)
		{
			_obj->colliders.push_back(this);
		}

		Vector3D SphereCollider::GetPosition()
		{
			return center * object->GetWorldTM();
		}

		Quaternion SphereCollider::GetRotation()
		{
			return object->GetRotation();
		}

		Vector3D SphereCollider::GetScale()
		{
			Vector3D scl{ object->GetScale() };
			float sclMax = std::max(std::max(scl.x, scl.y), scl.z);
			float sizeMax = std::max(std::max(size.x, size.y), size.z);

			return Vector3D(sclMax * sizeMax, sclMax * sizeMax, sclMax * sizeMax);
		}

		float SphereCollider::GetLength()
		{
			return (GetScale() * 0.5f).Length();
		}

		Matrix4x4 SphereCollider::GetLocalTM()
		{
			return ToTransformMatrix(center, Quaternion::Identity(), size);
		}

		Matrix4x4 SphereCollider::GetWorldTM()
		{
			return GetLocalTM() * object->GetWorldTM();
		}

		Vector3D SphereCollider::GetSize()
		{
			float sizeMax = std::max(std::max(size.x, size.y), size.z);
			return Vector3D(sizeMax, sizeMax, sizeMax);
		}

		Vector3D SphereCollider::GetCenter()
		{
			return center;
		}

		AABB SphereCollider::GetAABB()
		{
			Vector3D pos{ GetPosition() };
			Vector3D scl{ GetScale() };

			return AABB(pos, scl.x * 1.0f);
		}

		Vector3D SphereCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Vector3D pos{ GetPosition() };
			Vector3D scl{ GetScale() };

			return _direction * 0.5f * scl.x + pos;
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

		Matrix3x3 SphereCollider::GetInertiaTensor(float _mass)
		{
			Vector3D scl{ GetScale() };

			float radius = 0.5f * scl.x;
			float I{ (2.f / 5.f) * _mass * radius * radius };

			return inertia =
			{
				I, 0.f, 0.f,
				0.f, I, 0.f,
				0.f, 0.f, I
			};
		}

		size_t SphereCollider::GetType()
		{
			return (size_t)ShapeType::SPHERE;
		}
	}
}
