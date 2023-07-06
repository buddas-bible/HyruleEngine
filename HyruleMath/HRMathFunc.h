#pragma once

namespace Hyrule
{
	struct Vector3D;
	struct Vector4D;
	struct Matrix3x3;
	struct Matrix4x4;
	struct Quaternion;

	inline float ToDegree(const float _rad) noexcept;

	inline float ToRadian(const float _deg) noexcept;

	Matrix4x4 ToTranslateMatrix(const Vector3D& _euler) noexcept;

	Matrix4x4 ToScaleMatrix(const Vector3D& _euler) noexcept;

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept;

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

	Matrix4x4 ToMatrix(const Quaternion&) noexcept;

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