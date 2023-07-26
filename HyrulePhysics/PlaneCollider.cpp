#include "PlaneCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		PlaneCollider::PlaneCollider(Object* _obj, COLLIDER_INFO* _info) noexcept :
			Collider(_obj),
			shape(Shapes::planeShape)
		{
			this->SetSize(_info->colliderSize);
			this->SetCenter(_info->colliderCenter);
		}

		Vector3D PlaneCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Matrix4x4 objectTM = object->GetWorldTM();
			Matrix4x4 colliderTM = ToTransformMatrix(center, Quaternion::Identity(), size);

			Matrix4x4 colliderWorld = colliderTM *= objectTM;
			colliderWorld.m[3] = { 0.f, 0.f, 0.f, 1.f };
			Matrix4x4 invColliderWorld = colliderWorld.Inverse();

			float maxDist{ FLT_MIN };
			size_t index{ 0 };
			Vector3D dir{ (_direction * invColliderWorld).Normalized() };

			for (size_t i = 0; i < shape->GetPoints().size(); i++)
			{
				float dist{ shape->GetPoints()[i].Dot(dir) };

				if (dist > maxDist)
				{
					maxDist = dist;
					index = i;
				}
			}

			return shape->GetPoints()[index] * colliderTM;
		}

		Face PlaneCollider::FindSupportFace(const Vector3D&)
		{
			return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
		}
	}
}