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
		}

		Vector3D SphereCollider::FindFarthestPoint(const Vector3D& _direction)
		{
			Matrix4x4 world = object->GetWorldTM();
			Vector3D pos{ world.e[3] };

			Vector3D scl{ world.e[0] };
			float max{ scl.Length() };

			for (auto i = 1; i < 3; i++)
			{
				scl = world.e[i];
				float temp{ scl.Length() };

				if (max < temp)
				{
					max = temp;
				}
			}


			auto tt = _direction * 0.5f * max + pos;
			

			// tt += Vector3D::Zero();
			return tt;
		}

		Face SphereCollider::FindSupportFace(const Vector3D&)
		{
			return Face(Vector3D(), Vector3D(), Vector3D(), 0, 1, 2);
		}
	}
}
