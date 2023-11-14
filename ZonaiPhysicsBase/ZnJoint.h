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
							ZnJoint() noexcept = default;
		virtual				~ZnJoint() noexcept = 0;

	public:
		/**
		������Ʈ�� ����Ʈ�� ������.
		�� �� �ϳ��� NULL�� �� ����.
		*/
		virtual void		SetObject(ZnObject*, ZnObject*) noexcept = 0;
		virtual void		GetObject(ZnObject*&, ZnObject*&) const noexcept = 0;
		
		/**
		������Ʈ�� ������
		*/
		virtual void		SetLocalPosition(const Vector3D&) noexcept = 0;
		virtual Vector3D	GetLocalPosition() const noexcept = 0;

		/**
		������Ʈ�� �����̼�
		*/
		virtual void		SetLocalQuaternion(const Quaternion&) noexcept = 0;
		virtual Quaternion	GetLocalQuaternion() const noexcept = 0;

		/**
		������Ʈ0�� �������� ������Ʈ1�� ��� �ӵ��� ��ȯ��.
		*/
		virtual Vector3D	GetRelativeLinearVelocity() const noexcept = 0;
		virtual Vector3D	GetRelativeAngularVelocity() const noexcept = 0;

		/**
		����Ʈ �ı� ���� ������
		*/
		virtual void		SetBreakForce(float _force, float _torque) noexcept = 0;
		virtual void		GetBreakForce(float& _force, float& _torque) const noexcept = 0;
	};
}