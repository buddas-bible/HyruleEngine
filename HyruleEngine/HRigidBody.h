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
		/// ������ ����
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
�ݶ��̴��� ���� ������Ʈ�� �浹 �̺�Ʈ�� �����Ŵ.
��ü�� ���� ������ �浹 ������ �� �� �߰����� ������ ���� ����.
*/