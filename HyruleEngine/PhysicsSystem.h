#pragma once
#include "System.h"

#include <string>
#include "framework.h"


namespace Hyrule
{
	namespace Physics
	{
		class IPhysics;
		class IRigidBody;
		class ICollider;
		struct PHYSICALLYOBJECT_INFO;
	}

	class PhysicsSystem : System<PhysicsSystem>
	{
	public:
		PhysicsSystem() noexcept = default;
		~PhysicsSystem() noexcept = default;

	private:
		Physics::IPhysics* physicsEngine;

	public:
		bool LoadPhysicsDLL(const std::wstring&, HWND);

		void CollisionDetection() noexcept;
		void CollisionResponse(float) noexcept;
		void Finalize();

	public:
		Physics::ICollider* AddCollider(const std::wstring&, Physics::PHYSICALLYOBJECT_INFO*);
		Physics::IRigidBody* AddRigidBody(const std::wstring&);
	};
}

