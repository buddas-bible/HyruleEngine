#pragma once

#include "Collider.h"

namespace Hyrule
{
	class GameObject;

	namespace Physics
	{
		class ICollider;
	}

	class BoxCollider : public Collider
	{
	public:
		BoxCollider() = delete;
		BoxCollider(GameObject*) noexcept;
		virtual ~BoxCollider() noexcept;

	private:
		bool isColliding;
		Physics::ICollider* collider;

	public:
		virtual void SetTrigger(bool) override;
		virtual void SetSize(const Vector3D&) override;
		virtual void SetCenter(const Vector3D&) override;
		virtual bool isCollision() noexcept override;


	public:
		// virtual void Awake() abstract;
		// virtual void Start() abstract;
		virtual void FixedUpdate() override;
		virtual void PrePhysicsUpdate() override;
		virtual void PhysicsUpdate() override;
		virtual void LatePhysicsUpdate() override;
		virtual void Update() override;
		// virtual void LateUpdate() override;
		// virtual void Render() override;

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		// virtual void OnCollisionEnter(Collider*) abstract;
		// virtual void OnCollisionStay(Collider*) abstract;
		// virtual void OnCollisionExit(Collider*) abstract;

		// virtual void OnCollisionEnter() abstract;
		// virtual void OnCollisionStay() abstract;
		// virtual void OnCollisionExit() abstract;

		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void OnDestroy() override;
	};
}

