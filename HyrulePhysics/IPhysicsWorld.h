#pragma once

namespace Hyrule
{
	class ICollider;
	class IRigidBody;

	class IPhysicsWorld
	{
	public:
		IPhysicsWorld() noexcept {};
		virtual ~IPhysicsWorld() noexcept {};

	public:
		virtual ICollider* AddCollider() abstract;
		virtual IRigidBody* AddRigidBody() abstract;

	public:
		virtual int Initialize() abstract;
		virtual void CollisionCheck() abstract;
		virtual void RigidSimulation(float) abstract;
		virtual void WorldReset() abstract;
		virtual void Finalize() abstract;

		virtual void SetGravity(float) abstract;
	};
}