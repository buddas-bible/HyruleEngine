#pragma once

namespace Hyrule
{
	class Vector3D;
	class Vector4D;
	class Matrix4x4;
	class Quaternion;

	/// <summary>
	/// 라디안을 각도로 바꿈
	/// </summary>
	inline float ToDegree(const float _rad) noexcept;

	/// <summary>
	/// 각도를 라디안으로 바꿈
	/// </summary>
	inline float ToRadian(const float _deg) noexcept;

	Matrix4x4 ToTranslateMatrix(const Vector3D& _vec) noexcept
	{
		return Matrix4x4
		{
			1.f,	0.f,	0.f,	0.f,
			0.f,	1.f,	0.f,	0.f,
			0.f,	0.f,	1.f,	0.f,
			_vec.x, _vec.y, _vec.z, 1.f
		};
	}

	Matrix4x4 ToScaleMatrix(const Vector3D& _vec) noexcept
	{
		return Matrix4x4
		{
			_vec.x,	0.f,	0.f,	0.f,
			0.f,	_vec.y,	0.f,	0.f,
			0.f,	0.f,	_vec.z,	0.f,
			0.f,	0.f,	0.f,	1.f
		};
	}

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl);

	/// <summary>
	/// 사원수 선형 보간
	/// 정규화된 두 쿼터니언을 받아 보간함.
	/// t는 1.f ~ 0.f
	/// </summary>
	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);

	/// <summary>
	/// 사원수 구형 보간
	/// 정규화된 두 쿼터니언을 받아 보간함.
	/// t는 1.f ~ 0.f
	/// </summary>
	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

	/// <summary>
	/// 오일러 각을 쿼터니언으로 바꿈
	/// </summary>
	Quaternion ToQuaternion(const Vector3D& _euler);

	/// <summary>
	/// 축각을 쿼터니언으로 바꿈
	/// </summary>
	Quaternion ToQuaternion(const Vector4D& _axisAngle);

	/// <summary>
	/// 회전 행렬을 쿼터니언으로 바꿈
	/// </summary>
	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept;

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