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
		위치
		*/
		virtual Vector3D	GetPosition() const = 0;
		virtual void		SetPosition(const Vector3D& _position) = 0;

		/**
		회전
		*/
		virtual Quaternion	GetQuaternion() const = 0;
		virtual void		SetQuaternion(const Quaternion& _quaternion) = 0;

		virtual void		SetTransform(const Vector3D& _position, const Quaternion& _quaternion);

		/**
		유저 데이터
		*/
		virtual void*		GetUserData() const = 0;
		virtual void		SetUserData(void* _userData) = 0;

	};
}