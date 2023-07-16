#pragma once

#include "Collider.h"

namespace Hyrule
{
	class GameObject;

	namespace Physics
	{
		class ICollider;
	}

	class MeshCollider : public Collider
	{
	public:
		MeshCollider() = delete;
		MeshCollider(GameObject*) noexcept;
		virtual ~MeshCollider() noexcept;

	private:
		bool isColliding;
		Physics::ICollider* collider;

	public:
		virtual void SetTrigger(bool) override;
		virtual void SetSize(const Vector3D&) override;
		virtual void SetCenter(const Vector3D&) override;
		virtual bool IsColliding() override;

	public:

		virtual void Awake() abstract;
		virtual void Start() abstract;
		virtual void FixedUpdate() abstract;
		virtual void Update() abstract;
		virtual void LateUpdate() abstract;
		virtual void Render() abstract;

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		virtual void OnCollisionEnter(Collider*) abstract;
		virtual void OnCollisionStay(Collider*) abstract;
		virtual void OnCollisionExit(Collider*) abstract;

		virtual void OnCollisionEnter() abstract;
		virtual void OnCollisionStay() abstract;
		virtual void OnCollisionExit() abstract;

		virtual void OnEnable() abstract;
		virtual void OnDestroy() abstract;
	};
}

