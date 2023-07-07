#pragma once

#include "Collider.h"

namespace Hyrule
{
	namespace Physics
	{
		class BoxCollider : public Collider
		{
			virtual void SetWorldTransformMatrix(const Matrix4x4&) override;

			virtual void SetTrigger(bool) override;
			virtual void SetSize(const Vector3D&) override;
			virtual void SetCenter(const Vector3D&) override;

			virtual bool IsColliding() override;
		};
	}
}
