#include "Simplex.h"

namespace Hyrule
{
	namespace Physics
	{


		Hyrule::Vector3D& Simplex::operator[](int _i)
		{
			return points[_i];
		}

		void Simplex::push_back(const Vector3D& _vec)
		{
			points.push_back(_vec);
		}


		size_t Simplex::size()
		{
			return points.size();
		}

		void Simplex::SetIndices()
		{
			index = 
			{
				0, 2, 1,		// A, C, B
				0, 1, 3,		// A, B, D
				0, 3, 2,		// A, D, C
				2, 3, 1,		// C, D, B
			};
		}

		std::vector<Vector3D>& Simplex::operator=(const std::vector<Vector3D>& _points)
		{
			this->points = _points;
			return this->points;
		}
	}
}