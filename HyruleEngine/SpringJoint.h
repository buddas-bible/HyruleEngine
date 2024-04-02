#pragma once
#include "Component.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class Entity;
	class RigidBody;
	class Vector3D;

	namespace Physics
	{
		class IRigidBody;
		class ISpringJoint;
	}

	class SpringJoint : public Component
	{
	public:
		SpringJoint() = delete;
		SpringJoint(Entity*);
		~SpringJoint() override = default;

	private:
		Physics::ISpringJoint* iJoint;
		Vector3D position;
	};

}

