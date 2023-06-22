#pragma once
#include "Component.h"

#include "HRVector.h"
#include "HRMatrix.h"

namespace Hyrule
{
	class Transform : public Component
	{
	public:
		Transform() = default;
		virtual ~Transform() = default;

	private:
		Vector3D position;
		Vector3D rotation;
		Vector3D scale;

	public:
		Vector3D GetLocalPosition();
		Vector3D GetLocalRotation();
		Vector3D GetLocalScale();

		Matrix4x4 GetLocalMatrix();
		Matrix4x4 GetWorldMatrix();
	};
}

