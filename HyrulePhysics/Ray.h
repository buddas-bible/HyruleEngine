#pragma once
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		struct Ray
		{
			Vector3D position;
			Vector3D direction;
		};

        struct Segment
        {
            Vector3D position;
            Vector3D direction;
            float length;
        };
	}
}

