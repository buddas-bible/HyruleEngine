#pragma once
#include "Component.h"

namespace Hyrule
{
	class GameObject;
	class Vector3D;

	namespace Physics {
		class IRigidBody;
	}

	class RigidBody : public Component
	{
	public:
		RigidBody() = delete;
		RigidBody(GameObject*) noexcept;
		virtual ~RigidBody() = default;

		/// 그저 물리엔진에서의 강체와 이벤트를 연결해주는 무언가.
		/// 강체에 이벤트가... 있던가...?
	private:
		Physics::IRigidBody* rigidbody;

	public:
		void AddForce(const Vector3D&) const noexcept;
		void AddTorque(const Vector3D&) const noexcept;

	public:
		/// <summary>
		/// 물리량 조절
		/// </summary>
		void SetMess(const float) noexcept;
		float GetMess() const noexcept;

		void SetVelocity(const Hyrule::Vector3D&) noexcept;
		Hyrule::Vector3D GetVelocity() const noexcept;

		void SetAngularVelocity(const Hyrule::Vector3D&) noexcept;
		Hyrule::Vector3D GetAngularVelocity() const noexcept;

		bool isSleeping() const noexcept;

		bool isKinematic() const noexcept;
		void isKinematic(const bool) noexcept;


	public:
		virtual void Awake() override {}
		virtual void Start() override {}
		virtual void FixedUpdate() override {}
		virtual void Update() override;
		virtual void LateUpdate() override {}
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

		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void OnDestroy() override;
	};
}


/*
콜라이더를 가진 오브젝트에 충돌 이벤트를 실행시킴.
강체는 정지 했으면 충돌 감지만 할 뿐 추가적인 연산을 하지 않음.
*/