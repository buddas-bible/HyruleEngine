#include "Face.h"


namespace Hyrule
{
	namespace Physics
	{
		Face::Face(
			const Vector3D& _v0, const Vector3D& _v1, const Vector3D& _v2, 
			size_t _i0, size_t _i1, size_t _i2) :
			point{ _v0, _v1, _v2 }, index{_i0, _i1, _i2},
			normal{}, center{}
		{
			Vector3D temp{ _v0 - _v1 };
			this->normal = temp.Cross(_v2 - _v1);

			this->center = (_v0 + _v1 + _v2) / 3;
		}

	}
}