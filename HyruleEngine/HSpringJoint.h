#pragma once
#include "HComponent.h"
#include "HyruleMath.h"

namespace hyrule
{
	class HEntity;
	class HRigidBody;
	class Vector3D;

	namespace Physics
	{
		class IRigidBody;
		class ISpringJoint;
	}

	class HSpringJoint : public HComponent
	{
	public:
		HSpringJoint() = delete;
		HSpringJoint(HEntity*);
		~HSpringJoint() override = default;

	private:
		Physics::ISpringJoint* iJoint;
		Vector3D position;
	};

}

