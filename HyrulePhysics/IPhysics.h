#pragma once

namespace Hyrule
{
	class IPhysics
	{
	public:
		IPhysics() noexcept {};
		virtual ~IPhysics() noexcept {};

	public:
		virtual int Initialize() abstract;
		virtual void CollisionCheck() abstract;
		virtual void RigidSimulation() abstract;
		virtual void WorldReset() abstract;
		virtual void Finalize() abstract;
	};
}