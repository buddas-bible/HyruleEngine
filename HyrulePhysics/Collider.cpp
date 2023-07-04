#include "Collider.h"

#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{



		Matrix3x3 Collider::GetInertiaTensor(float _mess) noexcept
		{
			if (shape)
			{
				return shape->GetInertiaTensor(_mess);
			}

			return Matrix3x3{};
		}

		Hyrule::Vector3D Collider::GetCenterOfMess() noexcept
		{
			if (shape)
			{
				return shape->GetCenterOfMess();
			}

			return Vector3D{};
		}
	}
}