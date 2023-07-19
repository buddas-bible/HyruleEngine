#pragma once
#include "HRConstant.h"

namespace Hyrule
{
	struct Vector3D;
	struct Vector4D;
	struct Matrix3x3;
	struct Matrix4x4;
	struct Quaternion;

	/// <summary>
	/// 라디안을 각도로 바꿈
	/// </summary>
	constexpr float ToDegree(const float _rad) noexcept
	{
		return _rad * (180.0f / PI<float>);
	}

	/// <summary>
	/// 각도를 라디안으로 바꿈
	/// </summary>
	constexpr float ToRadian(const float _deg) noexcept
	{
		return _deg * (PI<float> / 180.f);
	}

	Matrix4x4 ToTranslateMatrix(const Vector3D& _euler) noexcept;

	Matrix4x4 ToScaleMatrix(const Vector3D& _scl) noexcept;

	Matrix4x4 ToScaleMatrix(const float _scl) noexcept;

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept;

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const float _scl) noexcept;

	void Decompose(Vector4D& _pos, Quaternion& _rot, Vector4D& _scl, const Matrix4x4& _matrix) noexcept;

	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept;

	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept;

	Quaternion RotateVectorToVectorQuaternion(const Vector3D&, const Vector3D&);
	
	Quaternion ToQuaternion(const Vector3D& _euler) noexcept;

	Quaternion ToQuaternion(const Vector4D& _axisAngle) noexcept;

	Quaternion ToQuaternion(const Vector3D& _axis, float _angle) noexcept;

	Quaternion ToQuaternion(const Matrix3x3& _rotMatrix) noexcept;

	Vector3D ToEuler(const Quaternion&) noexcept;

	Vector4D ToAxisAngle(const Quaternion&) noexcept;

	Matrix4x4 ToMatrix4(const Quaternion&) noexcept;

	Matrix3x3 ToMatrix3(const Vector3D&, const float) noexcept;

	// Vector4D& operator*=(Vector4D&, const Matrix4x4&) noexcept;
	// Vector4D operator*(const Vector4D&, const Matrix4x4&) noexcept;
	// 
	// Vector3D& operator*=(Vector3D&, const Matrix4x4&) noexcept;
	// Vector3D operator*(const Vector3D&, const Matrix4x4&) noexcept;

	// ToEuler (축각)
	// ToEuler (행렬)
	// 
	// ToAxisAngle (오일러)
	// ToAxisAngle (행렬)
	// 
	// ToMatrix (오일러)
	// ToMatrix (축각)
	// 
	// 같은 함수도 있으면 좋지 않을까?
	// 또 쿼터니언 맴버 함수로 있는 변환 함수들도 다 여기로 와야할듯.
}