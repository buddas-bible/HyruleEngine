#pragma once
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;
	namespace Physics
	{
		struct Face
		{
			Face() = delete;
			Face(const Vector3D&, const Vector3D&, const Vector3D&, 
				size_t, size_t, size_t);
			Vector3D point[3];
			size_t index[3];
			Vector3D normal;
			Vector3D center;
		};
	}
}

