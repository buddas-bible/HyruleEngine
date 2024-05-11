#pragma once
#include "HRConstant.h"

namespace hyrule
{
	struct Vector3D;
	struct Vector4D;
	struct Matrix3x3;
	struct Matrix4x4;
	struct Quaternion;

	/// <summary>
	/// ������ ������ �ٲ�
	/// </summary>
	constexpr float ToDegree(const float _rad)
	{
		return _rad * (180.0f / PI<float>);
	}

	/// <summary>
	/// ������ �������� �ٲ�
	/// </summary>
	constexpr float ToRadian(const float _deg)
	{
		return _deg * (PI<float> / 180.f);
	}

	Matrix4x4 ToTranslateMatrix(const Vector3D& _euler);

	Matrix4x4 ToScaleMatrix(const Vector3D& _scl);

	Matrix4x4 ToScaleMatrix(const float _scl);

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl);

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const float _scl);


	Vector3D DecomposPosition(const Matrix4x4& _mat);

	Quaternion DecomposRotation(const Matrix4x4& _mat);

	Vector3D DecomposScale(const Matrix4x4& _mat);

	void Decompose(const Matrix4x4& _matrix, Vector3D& _pos, Quaternion& _rot, Vector3D& _scl);


	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t);

	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t);


	Vector3D VectorRotateFromQuaternion(const Vector3D& _vec, const Quaternion& _q);

	Quaternion RotateVectorToVectorQuaternion(const Vector3D& _from, const Vector3D& _to);
	
	Quaternion ToQuaternion(const Vector3D& _euler);

	Quaternion ToQuaternion(const Vector4D& _axisAngle);

	Quaternion ToQuaternion(const Vector3D& _axis, float _angle);

	Quaternion ToQuaternion(const Matrix3x3& _rotMatrix);

	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix);


	Vector3D ToEuler(const Quaternion& _q);


	Vector4D ToAxisAngle(const Quaternion& _q);


	Matrix3x3 ToMatrix3(const Quaternion& _q);

	Matrix4x4 ToMatrix4(const Quaternion& _q);

	Matrix3x3 ToMatrix3(const Vector3D& _axis, const float _angle);

	Matrix4x4 ToMatrix4(const Vector3D& _axis, const float _angle);

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