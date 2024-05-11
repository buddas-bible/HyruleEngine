#pragma once
#include "HComponent.h"
#include "HyruleMath.h"

namespace hyrule
{
	class HEntity;
	class Vector3D;

	namespace Physics
	{
		class IRigidBody;
	}

	class HRigidBody : public HComponent
	{
	public:
		HRigidBody() = delete;
		HRigidBody(HEntity*);
		~HRigidBody() override = default;

	private:
		Physics::IRigidBody* iRigidBody;
		Vector3D position;
		Quaternion rotation;

	public:
		void AddForce(const Vector3D&) const;
		void AddTorque(const Vector3D&) const;

	public:
		/// <summary>
		/// 물리량 조절
		/// </summary>
		void SetMass(const float);
		float GetMass() const;

		void SetVelocity(const Vector3D&);
		Vector3D GetVelocity() const;

		void SetAngularVelocity(const Vector3D&);
		Vector3D GetAngularVelocity() const;

		bool isSleeping() const;

		bool IsKinematic() const;
		void SetKinematic(const bool);
	};
}


/*
콜라이더를 가진 오브젝트에 충돌 이벤트를 실행시킴.
강체는 정지 했으면 충돌 감지만 할 뿐 추가적인 연산을 하지 않음.
*/