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
			Vector3D& A{ points[0] };
			Vector3D& B{ points[1] };
			Vector3D& C{ points[2] };
			Vector3D& D{ points[3] };

			index = {};
		}

		std::vector<Vector3D>& Simplex::operator=(const std::vector<Vector3D>& _points)
		{
			this->points = _points;
			return this->points;
		}
	}
}