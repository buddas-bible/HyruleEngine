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
		/// ������ ������ �� ����ϰ� ������
		/// ���̽� ������ �ĳ��� Ž���ϴ� ����̳�.
		/// ������ å�� ����Ǿ��ִ� ��Ŭ���̹� �˰����� �̿��ص� ������ ����.
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