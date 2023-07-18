#include "ConvexCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		ConvexCollider::ConvexCollider(COLLIDER_INFO* _info) noexcept
		{
			SetSize(_info->colliderSize);
			SetCenter(_info->colliderCenter);
		}

		Vector3D ConvexCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Matrix4x4 invWorld = object->GetWorldTM();
			Matrix4x4 world = invWorld;
			invWorld.m[3] = { 0.f, 0.f, 0.f, 1.f };
			invWorld = invWorld.Inverse();

			float minDist{ FLT_MIN };
			size_t index{ 0 };
			Vector3D dir{ (_direction * invWorld).Normalized() };

			// for (size_t i = 0; i < shape->GetPoints().size(); i++)
			// {
			// 	float dist{ shape->GetPoints()[i].Dot(dir) };
			// 
			// 	if (dist < minDist)
			// 	{
			// 		minDist = dist;
			// 		index = i;
			// 	}
			// }
			// 
			// return shape->GetPoints()[index] * world;
			return Vector3D();
		}

		Face ConvexCollider::FindSupportFace(const Vector3D&)
		{
			return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
		}
	}
}