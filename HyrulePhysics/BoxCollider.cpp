#include "BoxCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "Shape.h"
#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		BoxCollider::BoxCollider(COLLIDER_INFO* _info) noexcept
		{
			this->SetSize(_info->colliderSize);
			this->SetCenter(_info->colliderCenter);
			this->shape = Shapes::boxShape;
		}

		/// <summary>
		/// 지금은 깡으로 다 계산하고 있지만
		/// 페이스 단위로 쳐내고 탐색하는 방식이나.
		/// 오렌지 책에 설명되어있는 힐클라이밍 알고리즘을 이용해도 좋을거 같다.
		/// </summary>
		Vector3D BoxCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Matrix4x4 invWorld = object->GetWorldTM();
			Matrix4x4 world = invWorld;
			invWorld.m[3] = {0.f, 0.f, 0.f, 1.f};
			invWorld = invWorld.Inverse();

			float minDist{ FLT_MIN };
			size_t index{ 0 };
			Vector3D dir{ (_direction * invWorld).Normalized() };

			for (size_t i = 0; i < shape->GetPoints().size(); i++)
			{
				float dist{ shape->GetPoints()[i].Dot(dir) };

				if (dist < minDist)
				{
					minDist = dist;
					index = i;
				}
			}

			return shape->GetPoints()[index] * world;
		}

		Face BoxCollider::FindSupportFace(const Vector3D&)
		{
			return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
		}
	}
}