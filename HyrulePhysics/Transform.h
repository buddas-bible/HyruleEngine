#pragma once
#include "HyruleMath.h"


namespace Hyrule
{
	namespace Physics
	{
		class Transform
		{
		public:
			Transform() noexcept = default;
			Transform(Vector3D&, Quaternion&, Vector3D&) noexcept;
			~Transform() noexcept = default;

		private:
			Hyrule::Vector3D& position;
			Hyrule::Quaternion& rotation;
			Hyrule::Vector3D& scale;
			Hyrule::Matrix4x4& worldTM;

		public:
			Hyrule::Matrix4x4& GetWorldTransform();
		};
	}
}

