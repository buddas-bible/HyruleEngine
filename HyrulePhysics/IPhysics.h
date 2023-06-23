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
		virtual void Update() abstract;
		virtual void FixedUpdate() abstract;
		virtual void Finalize() abstract;
	};

	IPhysics* CreatePhysics();
	void ReleasePhysics(IPhysics*& _physics);
}