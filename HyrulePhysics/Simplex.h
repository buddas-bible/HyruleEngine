#pragma once

#include <vector>
#include "HyruleMath.h"


namespace Hyrule
{
	namespace Physics
	{
		class Simplex
		{
		public:
			Simplex() noexcept = default;
			~Simplex() noexcept = default;

			std::vector<Vector3D> points;
			std::vector<size_t> index;
		};
	}
}

