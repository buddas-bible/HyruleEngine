#pragma once
#include "IRigidBody.h"
#include "HyruleMath.h"

namespace Hyrule
{
	class Collider;
	class Transform;

	class RigidBody : public IRigidBody
	{
	public:
		RigidBody() noexcept = default;
		virtual ~RigidBody() noexcept = default;

	private:
		// Collider* collider;
		Transform* transform;

	private:
		/// <summary>
		/// ���⼭ �����ǰ� �����̼��� Ʈ������ �����ε�
		/// ��� �� ������ ����غ�����
		/// 
		/// Ʈ������ ������ ������ ���·� ������ ������?
		/// ��� ������Ʈ �޴°� �����ϰ�
		/// ������ �޾ƿ��°�...?
		/// </summary>
		float mess;							// ����
		float invMess;						// �� ����
		Vector3D velocity;					// �ӵ�
		Vector3D angularVelocity;			// ���ӵ�
		float dfriction;					// ����
		float sfriction;					// ����
		float restitution;					// �ݹ߰��
		Matrix3x3 inertiaTensor;			// �����ټ�
		Matrix3x3 invInertiaTensor;			// �������ټ�

		bool sleep;							// ������ �ִ� �����ΰ�?
		bool kinematic;
		bool gravityEnabled;

	private:
		Vector3D force;						// ��
		Vector3D torque;					// ��ũ

	public:
		void AddImpulse(const Vector3D&, const Vector3D&) noexcept;
		virtual void AddForce(const Vector3D&) noexcept override;
		virtual void AddTorque(const Vector3D&) noexcept override;

#pragma region GetSet
	public:
		virtual void SetMess(const float) noexcept override;
		virtual float GetMess() const noexcept override;

		virtual void SetVelocity(const Vector3D&) noexcept override;
		virtual Vector3D GetVelocity() const noexcept override;

		virtual void SetAngularVelocity(const Vector3D&) noexcept override;
		virtual Vector3D GetAngularVelocity() const noexcept override;

		virtual bool isSleeping() const noexcept override;
		virtual void isSleeping(const bool) noexcept override;

		virtual bool isKinematic() const noexcept override;
		virtual void isKinematic(const bool) noexcept override;
#pragma endregion GetSet
	};
}
