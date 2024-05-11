#pragma once
#include "HyruleMath.h"

namespace hyrule
{
	struct Vector3D;

	namespace Physics
	{
		struct Ray
		{
			Vector3D from;
			Vector3D direction;
			float length;
		};

		struct RaycastInfo
		{
			bool collision;
			std::string name;
			Vector3D position;
		};
	}
}

