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
			Vector3D AB{ _B - _A };
			Vector3D AC{ _C - _A };
			Vector3D BC{ _C - _B };
			this->normal = AB.Cross(AC);

			edge[0] = Edge(_A, _B, _i0, _i1);
			edge[0].SetNormal(AB.Cross(normal));
			
			edge[1] = Edge(_C, _A, _i2, _i0);
			edge[1].SetNormal(normal.Cross(AC));
			
			edge[2] = Edge(_B, _C, _i1, _i2);
			edge[2].SetNormal(BC.Cross(normal));

			this->center = (_A + _B + _C) / 3;
		}

		Face::~Face() noexcept
		{
			// delete[] edge;
		}

	}
}