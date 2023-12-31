#pragma once
#include "System.h"

#include "framework.h"
#include <string>


namespace Hyrule
{
	namespace Physics
	{
		class IPhysics;
		class IRigidBody;
		class ICollider;

		struct COLLIDER_INFO;
	}

	class PhysicsSystem : public System<PhysicsSystem>
	{
	public:
		PhysicsSystem() noexcept = default;
		~PhysicsSystem() noexcept = default;
		PhysicsSystem(const PhysicsSystem&) = delete;
		PhysicsSystem& operator=(const PhysicsSystem&) = delete;

	private:
		Physics::IPhysics* physicsEngine{};
		HMODULE physicsDLL;

	public:
		bool LoadPhysicsDLL(const std::wstring&, HWND);

		void CollisionDetection() noexcept;
		void ApplyObjectDestroy() noexcept;
		void CollisionResponse(float) noexcept;
		void Finalize();

	public:
		Physics::ICollider* CreateCollider(const std::wstring&, Physics::COLLIDER_INFO*);
		Physics::IRigidBody* CreateRigidBody(const std::wstring&);
	};
}

