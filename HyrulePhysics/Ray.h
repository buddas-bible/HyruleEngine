#pragma once
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		struct Ray
		{
			Vector3D from;
			Vector3D direction;
		};

		struct RaycastInfo
		{
			bool collision;
			std::string name;
			Vector3D position;
		};
	}
}

