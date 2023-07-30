#include "Simplex.h"

#include "Face.h"

namespace Hyrule
{
	namespace Physics
	{
		Simplex::~Simplex() noexcept
		{
			// for (auto& e : faceMap)
			// {
			// 	delete e.second;
			// 	e.second = nullptr;
			// }
		}

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

		void Simplex::SetFace()
		{
			size_t ind[] = {
				0, 1, 2,
				0, 3, 1,
				0, 2, 3,
				2, 1, 3,
			};

			for (size_t i = 0; i < 12; i += 3)
			{
				Face face{ points[ind[i]], points[ind[i + 1]], points[ind[i + 2]], ind[i], ind[i + 1], ind[i + 2] };
				float dist{ (face.normal).Dot(points[ind[i]]) };
				faceMap.insert(std::make_pair(dist, face));
			}
		}

		void Simplex::AddFace(size_t _i0, size_t _i1, size_t _i2)
		{
			Vector3D A{ points[_i0] };
			Vector3D B{ points[_i1] };
			Vector3D C{ points[_i2] };
			Vector3D AB{ B - A };
			Vector3D AC{ C - A };
			Vector3D ABC{ AB.Cross(AC) };
			Vector3D OA{ A.Normalized() };

			// Vector3D normal{ AB.Cross(AC) };
			float dist0{ ABC.Dot(A) };
			if (dist0 >= 0.f)
			{
				Face face{ A, B, C, _i0, _i1, _i2 };
				float dist{ (face.normal).Dot(A) };
				faceMap.insert(std::make_pair(dist, face));
			}
			else
			{
				Face face{ A, C, B, _i0, _i2, _i1 };
				float dist{ (face.normal).Dot(A) };
				faceMap.insert(std::make_pair(dist, face));
			}
		}

		std::vector<Vector3D>& Simplex::operator=(const std::vector<Vector3D>& _points)
		{
			this->points = _points;

			return this->points;
		}

		std::vector<Vector3D>& Simplex::operator=(std::vector<Vector3D>&& _points)
		{
			if (&points != &_points)
			{
				this->points = _points;
			}

			return this->points;
		}
	}
}