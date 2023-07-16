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

			Vector3D& operator[](int);
			std::vector<Vector3D>& operator=(const std::vector<Vector3D>&);
			
			void push_back(const Vector3D&);
			size_t size();

			void SetIndices();

			std::vector<Vector3D> points;
			std::vector<size_t> index;
		};
	}
}

