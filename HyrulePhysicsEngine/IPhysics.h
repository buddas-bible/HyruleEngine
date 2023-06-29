#pragma once
#include <string>


namespace Hyrule
{
	struct Vector3D;

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

			virtual void RemoveCollider(const std::wstring&, ICollider*) abstract;
			virtual void RemoveCollider(const std::wstring&, int) abstract;
			virtual void RemoveRigidBody(const std::wstring&) abstract;

		public:
			virtual long Initialize() abstract;
			virtual void CollisionCheck() abstract;
			virtual void RigidSimulation(float) abstract;
			virtual void WorldReset() abstract;
			virtual void Finalize() abstract;

			virtual void SetWorldGravity(const Hyrule::Vector3D&) abstract;
		};
	}
}