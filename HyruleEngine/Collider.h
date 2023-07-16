#pragma once
#include "Component.h"

#include <vector>

namespace Hyrule
{
	namespace Physics
	{
		class ICollider;
	}

	class GameObject;
	struct Vector3D;

	class Collider : public Component
	{
	public:
		Collider() = delete;
		Collider(GameObject*) noexcept;
		virtual ~Collider() noexcept;

	public:
		virtual void SetTrigger(bool) abstract;
		virtual void SetSize(const Vector3D&) abstract;
		virtual void SetCenter(const Vector3D&) abstract;
		virtual bool IsColliding() abstract;

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
		virtual void OnDisable() abstract;
		virtual void OnDestroy() abstract;
	};
}