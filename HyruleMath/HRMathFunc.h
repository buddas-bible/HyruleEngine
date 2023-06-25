#pragma once

namespace Hyrule
{
	class Vector3D;
	class Vector4D;
	class Matrix4x4;
	class Quaternion;

	/// <summary>
	/// ������ ������ �ٲ�
	/// </summary>
	inline float ToDegree(const float _rad) noexcept;

	/// <summary>
	/// ������ �������� �ٲ�
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
	/// ����� ���� ����
	/// ����ȭ�� �� ���ʹϾ��� �޾� ������.
	/// t�� 1.f ~ 0.f
	/// </summary>
	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);

	/// <summary>
	/// ����� ���� ����
	/// ����ȭ�� �� ���ʹϾ��� �޾� ������.
	/// t�� 1.f ~ 0.f
	/// </summary>
	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);

	/// <summary>
	/// ���Ϸ� ���� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Vector3D& _euler);

	/// <summary>
	/// �ఢ�� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Vector4D& _axisAngle);

	/// <summary>
	/// ȸ�� ����� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept;

	// ToEuler (�ఢ)
	// ToEuler (���)
	// 
	// ToAxisAngle (���Ϸ�)
	// ToAxisAngle (���)
	// 
	// ToMatrix (���Ϸ�)
	// ToMatrix (�ఢ)
	// 
	// ���� �Լ��� ������ ���� ������?
	// �� ���ʹϾ� �ɹ� �Լ��� �ִ� ��ȯ �Լ��鵵 �� ����� �;��ҵ�.
}