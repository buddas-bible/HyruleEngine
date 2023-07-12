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

		std::vector<Vector3D>& Simplex::operator=(const std::vector<Vector3D>& _points)
		{
			this->points = _points;
			return this->points;
		}
	}
}