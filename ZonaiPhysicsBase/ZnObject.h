#pragma once

namespace ZonaiMath
{
	class Vector3D;
	class Quaternion;
}

namespace ZonaiPhysics
{
	using namespace ZonaiMath;

	class ZnObject
	{
	public:
							ZnObject() = default;
		virtual				~ZnObject() = 0;

	public:
		/**
		��ġ
		*/
		virtual Vector3D	GetPosition() const = 0;
		virtual void		SetPosition(const Vector3D& _position) = 0;

		/**
		ȸ��
		*/
		virtual Quaternion	GetQuaternion() const = 0;
		virtual void		SetQuaternion(const Quaternion& _quaternion) = 0;

		virtual void		SetTransform(const Vector3D& _position, const Quaternion& _quaternion);

		/**
		���� ������
		*/
		virtual void*		GetUserData() const = 0;
		virtual void		SetUserData(void* _userData) = 0;

	};
}