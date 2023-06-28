#pragma once
#include <string>


namespace Hyrule
{
	namespace Physics
	{
		class ICollider;
		class IRigidBody;

		class IPhysics
		{
		public:
			IPhysics() noexcept {};
			virtual ~IPhysics() noexcept {};

		public:
			virtual ICollider* AddCollider(const std::wstring&) abstract;
			virtual IRigidBody* AddRigidBody(const std::wstring&) abstract;

		public:
			virtual long Initialize() abstract;
			virtual void CollisionCheck() abstract;
			virtual void RigidSimulation(float) abstract;
			virtual void WorldReset() abstract;
			virtual void Finalize() abstract;

			virtual void SetGravity(float) abstract;
		};
	}
}