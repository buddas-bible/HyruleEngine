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
			// 콜라이더 위치 + 디렉션 방향 * 길이 (근데? 스케일값에 영향을 받아야하고, 콜라이더 사이즈도 영향을 받아야함)
			
			// 여러 축의 스케일
			Vector4D length{ Vector3D{0.5f, 0.5f, 0.5f}.Normalized(), 1.f };

			length *= (world * ToScaleMatrix(size));

			return Vector3D();
		}
	}
}
