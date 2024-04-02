#pragma once
#include "Singleton.h"

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

	class PhysicsSystem : public Singleton<PhysicsSystem>
	{
	private:
		Physics::IPhysics* physicsEngine{};
		HMODULE physicsDLL;

	public:
		bool LoadPhysicsDLL(const std::wstring&, HWND);

		void CollisionDetection();
		void ApplyObjectDestroy();
		void CollisionResponse(float);
		void Finalize();

	public:
		Physics::ICollider* CreateCollider(const std::wstring&, Physics::COLLIDER_INFO*);
		Physics::IRigidBody* CreateRigidBody(const std::wstring&);
	};
}

