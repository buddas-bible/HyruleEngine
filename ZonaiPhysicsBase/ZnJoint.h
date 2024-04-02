#pragma once

namespace ZonaiMath
{
	class Vector3D;
	class Quaternion;
}


namespace ZonaiPhysics
{
	using namespace ZonaiMath;
	
	class ZnObject;

	class ZnJoint
	{
	public:
							ZnJoint() = default;
		virtual				~ZnJoint() = 0;

	public:
		/**
		������Ʈ�� ����Ʈ�� ������.
		�� �� �ϳ��� NULL�� �� ����.
		*/
		virtual void		SetObject(ZnObject*, ZnObject*) = 0;
		virtual void		GetObject(ZnObject*&, ZnObject*&) const = 0;
		
		/**
		������Ʈ�� ������
		*/
		virtual void		SetLocalPosition(const Vector3D&) = 0;
		virtual Vector3D	GetLocalPosition() const = 0;

		/**
		������Ʈ�� �����̼�
		*/
		virtual void		SetLocalQuaternion(const Quaternion&) = 0;
		virtual Quaternion	GetLocalQuaternion() const = 0;

		/**
		������Ʈ0�� �������� ������Ʈ1�� ��� �ӵ��� ��ȯ��.
		*/
		virtual Vector3D	GetRelativeLinearVelocity() const = 0;
		virtual Vector3D	GetRelativeAngularVelocity() const = 0;

		/**
		����Ʈ �ı� ���� ������
		*/
		virtual void		SetBreakForce(float _force, float _torque) = 0;
		virtual void		GetBreakForce(float& _force, float& _torque) const = 0;
	};
}