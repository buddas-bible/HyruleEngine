#include "SphereCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"
#include "Object.h"
#include "SphereShape.h"

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
			Matrix4x4 world = object->GetWorldTM();
			// �ݶ��̴� ��ġ + �𷺼� ���� * ���� (�ٵ�? �����ϰ��� ������ �޾ƾ��ϰ�, �ݶ��̴� ����� ������ �޾ƾ���)
			
			// ���� ���� ������
			Vector4D length{ Vector3D{0.5f, 0.5f, 0.5f}.Normalized(), 1.f };

			length *= (world * ToScaleMatrix(size));

			return Vector3D();
		}
	}
}
