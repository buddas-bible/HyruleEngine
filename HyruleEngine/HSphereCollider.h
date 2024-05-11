#pragma once

#include "HCollider.h"

namespace hyrule
{
	class HEntity;

	namespace Physics
	{
		class ICollider;
	}

	class HSphereCollider : public HCollider
	{
	public:
		HSphereCollider() = delete;
		HSphereCollider(HEntity*);
		~HSphereCollider() override;

	private:
		bool isColliding;
		Physics::ICollider* collider;

	public:
		virtual void SetTrigger(bool) override;
		virtual void SetSize(const Vector3D&) override;
		virtual void SetCenter(const Vector3D&) override;
		virtual bool isCollision() override;

	public:
		virtual void PrePhysicsUpdate() override;
		virtual void PhysicsUpdate() override;
		virtual void LatePhysicsUpdate() override;
		virtual void Update() override;

		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void OnDestroy() override;
	};
}

