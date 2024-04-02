#pragma once

#include "Collider.h"

namespace Hyrule
{
	class Entity;

	namespace Physics
	{
		class ICollider;
	}

	class BoxCollider : public Collider
	{
	public:
		BoxCollider() = delete;
		BoxCollider(Entity*);
		~BoxCollider() override;

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

