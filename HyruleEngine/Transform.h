#pragma once
#include <string>
#include <vector>

#include "HyruleMath.h"
#include "Component.h"

namespace Hyrule
{
	class GameObject;

	class Transform : public Component
	{
	public:
		Transform() = delete;
		Transform(GameObject*) noexcept;
		virtual ~Transform() noexcept = default;

	private:
		Vector3D position;
		Quaternion rotation;
		Vector3D scale;

	private:
		Hyrule::Transform* parent;
		std::vector<Transform*> children;

	public:
		/// <summary>
		/// 트랜스폼 관련 함수
		/// </summary>
		Vector3D GetLocalPosition() noexcept;
		Vector3D GetWorldPosition() noexcept;
		void SetLocalPosition(const Vector3D&) noexcept;

		Vector3D GetLocalRotation() noexcept;
		Quaternion GetLocalQuaternion() noexcept;
		Quaternion GetWorldQuaternion() noexcept;
		void SetLocalQuaternion(const Quaternion&) noexcept;

		Vector3D GetLocalScale() noexcept;
		Vector3D GetWorldScale() noexcept;
		void SetLocalScale(const Vector3D&) noexcept;

		Matrix4x4 GetParentWorldMatrix() noexcept;

		Vector3D GetUp() noexcept;
		Vector3D GetForward() noexcept;
		Vector3D GetRight() noexcept;

		Matrix4x4 GetLocalMatrix() noexcept;
		Matrix4x4 GetWorldMatrix() noexcept;


	public:
		/// <summary>
		/// 부모자식 관련 함수
		/// </summary>
		Transform* GetParent() noexcept;
		void SetParent(Transform*) noexcept;
		void RemoveParent() noexcept;

		void AddChild(Transform*) noexcept;
		void RemoveChild(Transform*) noexcept;

		Transform* GetChild(const size_t) noexcept;
		std::vector<Transform*> Getchildren() noexcept;
		size_t GetChildCount() noexcept;
		Transform* FindChild(const std::wstring&) noexcept;

	public:
		virtual void Awake() final {}
		virtual void Start() final {}
		virtual void FixedUpdate() final {}
		virtual void PrePhysicsUpdate() final {};
		virtual void PhysicsUpdate() final {};
		virtual void LatePhysicsUpdate() final {};
		virtual void Update() final {}
		virtual void LateUpdate() final {}
		virtual void Render() final {}

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		virtual void OnCollisionEnter(Collider*) final {}
		virtual void OnCollisionStay(Collider*) final {}
		virtual void OnCollisionExit(Collider*) final {}

		virtual void OnCollisionEnter() final {}
		virtual void OnCollisionStay() final {}
		virtual void OnCollisionExit() final {}

		virtual void OnEnable() final {}
		virtual void OnDisable() final {}
		virtual void OnDestroy() final;
	};
}

