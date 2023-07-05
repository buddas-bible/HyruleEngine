#pragma once
#include "Component.h"

#include <string>
#include <vector>

#pragma comment(lib, "HyruleMath.lib")
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;
	struct Quaternion;
	struct Matrix4x4;

	class Transform : public Component
	{
	public:
		Transform() = delete;
		Transform(GameObject*);
		virtual ~Transform() noexcept;

	private:
		Hyrule::Vector3D position;
		Hyrule::Quaternion quaternion;
		Hyrule::Vector3D scale;

	private:
		Hyrule::Transform* parent;
		std::vector<Hyrule::Transform*> child;

	public:
		/// <summary>
		/// 트랜스폼 관련 함수
		/// </summary>
		Vector3D GetLocalPosition() noexcept;
		void SetLocalPosition(const Vector3D&) noexcept;
		Vector3D GetLocalRotation() noexcept;
		Quaternion GetLocalQuaternion() noexcept;
		void SetLocalQuaternion(const Quaternion&) noexcept;
		Quaternion GetWorldQuaternion() noexcept;
		Vector3D GetLocalScale() noexcept;
		void SetLocalScale(const Vector3D&) noexcept;

		Vector3D GetUp() noexcept;
		void SetUp(const Vector3D&) noexcept;
		Vector3D GetForward() noexcept;
		void SetForward(const Vector3D&) noexcept;
		Vector3D GetRight() noexcept;
		void SetRight(const Vector3D&) noexcept;

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
		size_t GetChildCount() noexcept;
		Transform* FindChild(const std::wstring&) noexcept;

	public:
		virtual void Awake() override {}
		virtual void Start() override {}
		virtual void FixedUpdate() override {}
		virtual void Update() override {}
		virtual void LastUpdate() override {}
		virtual void Render() override {}

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		virtual void OnCollisionEnter(Collider*) override {}
		virtual void OnCollisionStay(Collider*) override {}
		virtual void OnCollisionExit(Collider*) override {}

		virtual void OnCollisionEnter() override {}
		virtual void OnCollisionStay() override {}
		virtual void OnCollisionExit() override {}

		virtual void OnEnable() override {}
		virtual void OnDestroy() override;
	};
}

