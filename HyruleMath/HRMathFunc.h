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
	/// ������ ������ �ٲ�
	/// </summary>
	constexpr float ToDegree(const float _rad) noexcept
	{
		return _rad * (180.0f / PI<float>);
	}

	/// <summary>
	/// ������ �������� �ٲ�
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


    Vector3D DecomposPosition(const Matrix4x4& _mat) noexcept;

    Quaternion DecomposRotation(const Matrix4x4& _mat) noexcept;

    Vector3D DecomposScale(const Matrix4x4& _mat) noexcept;

    void Decompose(const Matrix4x4& _matrix, Vector3D& _pos, Quaternion& _rot, Vector3D& _scl) noexcept;


	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept;

	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept;


    Vector3D VectorRotateFromQuaternion(const Vector3D& _vec, const Quaternion& _q) noexcept;

	Quaternion RotateVectorToVectorQuaternion(const Vector3D&, const Vector3D&);
	

	Quaternion ToQuaternion(const Vector3D& _euler) noexcept;

    // ��� ����
	Quaternion ToQuaternionFromZYX(const Vector3D& _euler) noexcept;

    // ��� ����
	Quaternion ToQuaternionFromZXY(const Vector3D& _euler) noexcept;
	
    // ��� ����
    Quaternion ToQuaternionFromYXZ(const Vector3D& _euler) noexcept;
	
    // ��� ����
    Quaternion ToQuaternionFromYZX(const Vector3D& _euler) noexcept;
    
    // ��� ����
    Quaternion ToQuaternionFromXYZ(const Vector3D& _euler) noexcept;
    
    // ��� ����
    Quaternion ToQuaternionFromXZY(const Vector3D& _euler) noexcept;



	Quaternion ToQuaternion(const Vector4D& _axisAngle) noexcept;

	Quaternion ToQuaternion(const Vector3D& _axis, float _angle) noexcept;

	Quaternion ToQuaternion(const Matrix3x3& _rotMatrix) noexcept;

    Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept;

    Vector3D ToEulerFromDegree(const Vector3D& _degree) noexcept;

    Vector3D ToEuler(const Matrix3x3&) noexcept;

    Vector3D ToEuler(const Matrix4x4&) noexcept;


	Vector3D ToEuler(const Quaternion&) noexcept;

    // ��� ����
	Vector3D ToEulerXYZ(const Quaternion&) noexcept;
	
    // ��� ����
    Vector3D ToEulerYXZ(const Quaternion&) noexcept;
	
    // ��� ����
    Vector3D ToEulerZXY(const Quaternion&) noexcept;
    
    // ��� ����
    Vector3D ToEulerYZX(const Quaternion&) noexcept;
    
    // ��� ����
    Vector3D ToEulerXZY(const Quaternion&) noexcept;
    
    // ��� ����
    Vector3D ToEulerZYX(const Quaternion&) noexcept;


	Vector4D ToAxisAngle(const Quaternion&) noexcept;


    Matrix3x3 ToMatrix3(const Quaternion& _q) noexcept;

	Matrix4x4 ToMatrix4(const Quaternion&) noexcept;

	Matrix3x3 ToMatrix3(const Vector3D&, const float) noexcept;

	Matrix4x4 ToMatrix4(const Vector3D&, const float) noexcept;


    Matrix4x4 CameraLookAtLH(const Vector3D& _eyePos, const Vector3D& _focus, const Vector3D& _worldUp) noexcept;

    Matrix4x4 CameraLookToLH(const Vector3D& _eyePos, const Vector3D& _direction, const Vector3D& _worldUp) noexcept;

    Matrix4x4 CameraPerspectiveFovLH(float _angleY, float _ratio, float _near, float _far) noexcept;

    Matrix4x4 CameraOrthographicLH(float _width, float _height, float _near, float _far) noexcept;

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