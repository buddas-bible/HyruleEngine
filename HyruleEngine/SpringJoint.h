#pragma once
#include "Component.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class GameObject;
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
		SpringJoint(GameObject*) noexcept;
		virtual ~SpringJoint() = default;

	private:
		Physics::ISpringJoint* iJoint;
		Vector3D position;

	};

}

