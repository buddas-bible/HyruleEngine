#include "Face.h"


namespace Hyrule
{
	namespace Physics
	{
		Face::Face(
			const Vector3D& _A, const Vector3D& _B, const Vector3D& _C,
			size_t _i0, size_t _i1, size_t _i2) noexcept :
			vec{ _A, _B, _C }, index{ _i0, _i1, _i2 },
			normal{}, center{}
		{
			Vector3D AB{ (_B - _A).Normalized() };
			Vector3D AC{ (_C - _A).Normalized() };
			Vector3D BC{ (_C - _B).Normalized() };
			this->normal = AB.Cross(AC).Normalized();

			edge.push_back({ _A, _B, _i0, _i1 });
			edge[0].SetNormal(AB.Cross(normal).Normalized());

			edge.push_back({ _B, _C, _i1, _i2 });
			edge[1].SetNormal(BC.Cross(normal).Normalized());

			edge.push_back({ _C, _A, _i2, _i0 });
			edge[2].SetNormal(normal.Cross(AC).Normalized());

			this->center = (_A + _B + _C) / 3;
		}

		Face::Face(const std::vector<Edge>& edges) noexcept : 
			edge(edges)
		{
			// 엣지가 중복되지 않았다는 가정 하에...
			for (auto i = 0; i < edges.size(); i++)
			{
				vec.push_back(edges[i].vectorA);
				center += edges[i].vectorA;
			}

			Vector3D AB{ edge[0].direction };
			Vector3D AC{ edge[1].direction };

			normal = AB.Cross(AC);
			center /= (float)vec.size();
		}

		Face::~Face() noexcept
		{
			// delete[] edge;
		}


		void Face::Inverse() noexcept
		{

		}

		void Face::SetEdge() noexcept
		{
			edge.clear();

			for (size_t i = 0; i < vec.size(); i++)
			{
				size_t j = i + 1 % vec.size();

				edge.push_back({ vec[i], vec[j], i, j });
			}
		}
	}
}