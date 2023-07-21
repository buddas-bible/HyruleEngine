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
		virtual ~Collider() noexcept = default;

	public:
		virtual void SetTrigger(bool) abstract;
		virtual void SetSize(const Vector3D&) abstract;
		virtual void SetCenter(const Vector3D&) abstract;
		virtual bool isCollision() noexcept abstract;

	public:
		virtual void Awake() final {};
		virtual void Start() final {};
		virtual void FixedUpdate() abstract;
		virtual void Update() abstract;
		virtual void LateUpdate() final {};
		virtual void Render() final {};

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		virtual void OnCollisionEnter(Collider*)  final {};
		virtual void OnCollisionStay(Collider*) final {};
		virtual void OnCollisionExit(Collider*) final {};

		virtual void OnCollisionEnter() final {};
		virtual void OnCollisionStay() final {};
		virtual void OnCollisionExit() final {};

		virtual void OnEnable() abstract;
		virtual void OnDisable() abstract;
		virtual void OnDestroy() abstract;
	};
}