#include "BoxCollider.h"

namespace Hyrule
{
	namespace Physics
	{

		BoxCollider::BoxCollider(COLLIDER_INFO* _info) noexcept : Collider()
		{

		}

		void BoxCollider::SetTrigger(bool _isTrigger)
		{
			this->isTrigger = _isTrigger;
		}

		void BoxCollider::SetSize(const Vector3D& _size)
		{
			this->size = _size;
		}

		void BoxCollider::SetCenter(const Vector3D& _center)
		{
			this->center = _center;
		}

		bool BoxCollider::IsColliding()
		{
			return this->collided;
		}

		Vector3D BoxCollider::FindFarthestPoint(const Vector3D&)
		{
			return Vector3D();
		}
	}
}