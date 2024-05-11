#pragma once

#include "HCollider.h"

namespace hyrule
{
	class HEntity;

	namespace Physics
	{
		class ICollider;
	}

	class HBoxCollider : public HCollider
	{
	public:
		HBoxCollider() = delete;
		HBoxCollider(HEntity*);
		~HBoxCollider() override;

	private:
		bool isColliding;
		Physics::ICollider* collider;

	public:
		void SetTrigger(bool) override;
		void SetSize(const Vector3D&) override;
		void SetCenter(const Vector3D&) override;
		bool isCollision() override;


	public:
		void PrePhysicsUpdate() override;
		void PhysicsUpdate() override;
		void LatePhysicsUpdate() override;
		void Update() override;

		void OnEnable() override;
		void OnDisable() override;
		void OnDestroy() override;
	};
}

