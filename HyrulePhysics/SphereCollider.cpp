#include "SphereCollider.h"


namespace Hyrule
{
	namespace Physics
	{

		SphereCollider::SphereCollider(COLLIDER_INFO*) noexcept : Collider()
		{

		}

		Vector3D SphereCollider::FindFarthestPoint(const Vector3D&)
		{
			return Vector3D();
		}

		void SphereCollider::SetTrigger(bool)
		{

		}

		void SphereCollider::SetSize(const Vector3D&)
		{

		}

		void SphereCollider::SetCenter(const Vector3D&)
		{

		}

		bool SphereCollider::IsColliding()
		{
			return false;
		}
	}
}
