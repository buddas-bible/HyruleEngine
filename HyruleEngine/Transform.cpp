#include "Transform.h"

#include "GameObject.h"

namespace Hyrule
{

	Vector3D Transform::GetLocalPosition()
	{
		return position;
	}

	Vector3D Transform::GetLocalRotation()
	{
		return rotation;

	}

	Vector4D Transform::GetLocalQuaternion()
	{
		return quaternion;
	}

	Vector3D Transform::GetLocalScale()
	{
		return scale;
	}

	Matrix4x4 Transform::GetLocalMatrix()
	{
		

	}

	Matrix4x4 Transform::GetWorldMatrix()
	{

	}
}