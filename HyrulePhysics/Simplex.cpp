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
// 
// 		void Simplex::SetIndices()
// 		{
// 			index.insert({ 0, 2, 1 });
// 			index.insert({ 0, 1, 3 });
// 			index.insert({ 0, 3, 2 });
// 			index.insert({ 2, 3, 1 });
// 		}

		void Simplex::SetFace()
		{
			size_t ind[] = {
				0, 2, 1,
				0, 1, 3,
				0, 3, 2,
				2, 3, 1,
			};

			for (size_t i = 0; i < 12; i += 3)
			{
				// Face* face = new Face(points[ind[i]], points[ind[i + 1]], points[ind[i + 2]], ind[i], ind[i + 1], ind[i + 2]);
				Face face = Face(points[ind[i]], points[ind[i + 1]], points[ind[i + 2]], ind[i], ind[i + 1], ind[i + 2]);
				float dist = std::fabs((face.normal).Dot(face.vec[0]));
				faceMap.insert(std::make_pair(dist, face));
			}
		}

		void Simplex::AddFace(size_t _i0, size_t _i1, size_t _i2)
		{
			Vector3D A{ points[_i0] };
			Vector3D B{ points[_i1] };
			Vector3D C{ points[_i2] };
			Vector3D AB{ (B - A).Normalized() };
			Vector3D AC{ (C - A).Normalized() };
			Vector3D ABC{ AB.Cross(AC).Normalized()};
			Vector3D OC{ C.Normalized() };

			// ABC 노말 방향과 원점에서 C의 방향이 같으면 노말이 맞음.
			if (ABC.Dot(OC) >= 0.f)
			{
				Face face = Face(points[_i0], points[_i1], points[_i2], _i0, _i1, _i2);
				float dist = (face.normal).Dot(face.vec[0]);
				faceMap.insert(std::make_pair(dist, face));
			}
			else
			{
				Face face = Face(points[_i0], points[_i2], points[_i1], _i0, _i2, _i1);
				float dist = (face.normal).Dot(face.vec[0]);
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