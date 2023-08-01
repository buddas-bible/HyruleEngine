#pragma once
#include <string>

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		struct RaycastInfo
		{
			bool collision;
			std::string name;
			Vector3D position;
		};
	}
}