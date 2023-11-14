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
							ZnObject() noexcept = default;
		virtual				~ZnObject() noexcept = 0;

	public:
		/**
		��ġ
		*/
		virtual Vector3D	GetPosition() const noexcept = 0;
		virtual void		SetPosition(const Vector3D& _position) noexcept = 0;

		/**
		ȸ��
		*/
		virtual Quaternion	GetQuaternion() const noexcept = 0;
		virtual void		SetQuaternion(const Quaternion& _quaternion) noexcept = 0;

		virtual void		SetTransform(const Vector3D& _position, const Quaternion& _quaternion) noexcept;

		/**
		���� ������
		*/
		virtual void*		GetUserData() const noexcept = 0;
		virtual void		SetUserData(void* _userData) noexcept = 0;

	};
}