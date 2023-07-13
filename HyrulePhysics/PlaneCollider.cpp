#include "PlaneCollider.h"
#include "PHYSICALLYOBJECT_INFO.h"

namespace Hyrule
{
	namespace Physics
	{
		PlaneCollider::PlaneCollider(COLLIDER_INFO* _info) noexcept : Collider()
		{
			this->size = _info->colliderSize;
			this->center = _info->colliderCenter;
		}

		void PlaneCollider::SetTrigger(bool)
		{

		}

		void PlaneCollider::SetSize(const Vector3D&)
		{

		}

		void PlaneCollider::SetCenter(const Vector3D&)
		{

		}

		bool PlaneCollider::IsColliding()
		{

		}

		Vector3D PlaneCollider::FindFarthestPoint(const Vector3D&)
		{
			return Vector3D();
		}
	}
}