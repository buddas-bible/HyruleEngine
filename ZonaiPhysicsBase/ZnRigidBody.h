#pragma once
#include "ForceType.h"
#include "ZnObject.h"

namespace ZonaiMath
{
	class Vector3D;
	class Quaternion;
}

namespace ZonaiPhysics
{
	using DynamicLocks = unsigned char;
	
	enum class DynamicLock : DynamicLocks
	{
		LOCK_LINEAR_X = (1 << 0),
		LOCK_LINEAR_Y = (1 << 1),
		LOCK_LINEAR_Z = (1 << 2),
		LOCK_ANGULAR_X = (1 << 3),
		LOCK_ANGULAR_Y = (1 << 4),
		LOCK_ANGULAR_Z = (1 << 5)
	};

	using namespace ZonaiMath;

	class ZnRigidBody : public ZnObject
	{

	public:
							ZnRigidBody() = default;
		virtual				~ZnRigidBody() = 0;

	public:
		/**
		���� ������ ��ü�� ����
		*/
		virtual void		WakeUp() = 0;
		
		/**
		���� ���θ� ��ȯ��
		*/
		virtual bool		IsSleeping() const = 0;

		/**
		��ü�� �������� �����ϴ� �÷���
		*/
		virtual DynamicLocks GetDynamicLockFlags() const = 0;
		virtual void		SetDynamicLockFlag(DynamicLock flag, bool) = 0;
		virtual void		SetDynamicLockFlags(DynamicLocks flags) = 0;

		virtual void*		GetUserData() const = 0;
		virtual void		SetUserData(void*) = 0;

	public:
		/**
		����

		��ü�� ����.
		0�̸� ������ �������� �����.
		*/
		virtual float		GetMass() const = 0;
		virtual void		SetMass(float) = 0;
		virtual float		GetInvMass() const = 0;

		virtual Vector3D	GetInertiaTensor() const = 0;
		virtual void		SetInertiaTensor(const Vector3D&) = 0;

		/**
		���� ���� ���

		�����̳� �������� ��ҿ� ���� ��ü�� ������ ������.
		*/
		virtual float		GetLinearDamping() const = 0;
		virtual void		SetLinearDamping(float _damping) = 0;

		/**
		ȸ�� ���� ���

		�����̳� �������� ��ҿ� ���� ��ü�� ������ ������
		*/
		virtual float		GetAngularDamping() const = 0;
		virtual void		SetAngularDamping(float _damping) = 0;
		
		/**
		���ӵ�
		*/
		virtual Vector3D	GetLinearVelocity() const = 0;
		virtual void		SetLinearVelocity(const Vector3D& _velocity) = 0;
		
		/**
		���ӵ�
		*/
		virtual Vector3D	GetAngularVelocity() const = 0;
		virtual void		SetAngularVelocity(const Vector3D& _velocity) = 0;
		
		/**
		���ӵ� ����
		*/
		virtual float		GetMaxLinearVelocity() const = 0;
		virtual void		SetMaxLinearVelocity(const float&) = 0;

		/**
		���ӵ� ����
		*/
		virtual float		GetMaxAngularVelocity() const = 0;
		virtual void		SetMaxAngularVelocity(const float&) = 0;

		/**
		��ü�� ���� ���ϰų� ����
		*/
		virtual void		AddForce(const Vector3D& _force, ForceType _type = ForceType::Force) = 0;
		virtual void		ClearForce() = 0;

		/**
		��ü�� ��ũ�� ���ϰų� ����
		*/
		virtual void		AddTorque(const Vector3D& _torque, ForceType _type = ForceType::Force) = 0;
		virtual void		ClearTorque() = 0;
	};
}