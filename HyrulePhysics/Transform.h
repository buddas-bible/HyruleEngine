#pragma once
#include "HyruleMath.h"


namespace Hyrule
{
	class Transform
	{
	public:
		Transform() noexcept = default;
		Transform(Vector3D&, Quaternion&, Vector3D&) noexcept;
		~Transform() noexcept = default;

		Vector3D& position;
		Quaternion& rotation;
		Vector3D& scale;
	};
}

