#include "SphereCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		SphereCollider::SphereCollider(COLLIDER_INFO* _info) noexcept
		{
			SetSize(_info->colliderSize);
			SetCenter(_info->colliderCenter);
		}

		Vector3D SphereCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			// float L = size.x < size.y ? size.y : size.x;
			// L = L < size.z ? size.z : L;

			Matrix4x4 local = ToTransformMatrix(center, Quaternion::Identity(), size);
			// Matrix4x4 local = ToTransformMatrix(center, Quaternion::Identity(), L);
			Matrix4x4 world = object->GetWorldTM();

			auto tt = Vector4D(_direction, 1.f) * local * world;
			// local *= world;
			// Vector3D move = Vector3D(local.m[3].e00, local.m[3].e01, local.m[3].e02);
			// 
			// local.m[3].e00 = 0.f;
			// local.m[3].e01 = 0.f;
			// local.m[3].e02 = 0.f;
			// 
			// Vector4D temp = Vector4D(_direction, 1.f) * local;

			return Vector3D(tt.x, tt.y, tt.z);
		}

		Face SphereCollider::FindSupportFace(const Vector3D&)
		{
			return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
		}
	}
}
