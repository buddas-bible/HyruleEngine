#include "Transform.h"


namespace Hyrule
{
	Transform::Transform(
		Vector3D*& _pos, Quaternion*& _rot, Vector3D*& _scl) noexcept : 
		position(_pos), rotation(_rot), scale(_scl)
	{

	}
}