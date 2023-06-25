#pragma once

#include <cmath>
#include "HRVector.h"
#include "Quaternion.h"
#include "HRMatrix.h"
#include "HRConstant.h"

namespace Hyrule
{
	/// <summary>
	/// ������ ������ �ٲ�
	/// </summary>
	inline float ToDegree(const float _rad) noexcept
	{
		return _rad * (180.0f / PI<float>);
	}

	/// <summary>
	/// ������ �������� �ٲ�
	/// </summary>
	inline float ToRadian(const float _deg) noexcept
	{
		return _deg * (PI<float> / 180.f);
	}

	Matrix4x4 ToTranslate(const Vector3D& _vec) noexcept
	{
		return Matrix4x4
		{
			1.f,	0.f,	0.f,	0.f,
			0.f,	1.f,	0.f,	0.f,
			0.f,	0.f,	1.f,	0.f,
			_vec.x, _vec.y, _vec.z, 1.f
		};
	}

	Matrix4x4 ToScale(const Vector3D& _vec) noexcept
	{
		return Matrix4x4
		{
			_vec.x,	0.f,	0.f,	0.f,
			0.f,	_vec.y,	0.f,	0.f,
			0.f,	0.f,	_vec.z,	0.f,
			0.f,	0.f,	0.f,	1.f
		};
	}

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept
	{
		return ToScale(_scl) * _rot.ToMatrix() * ToTranslate(_pos);
	}

	/// <summary>
	/// ����� ���� ����
	/// ����ȭ�� �� ���ʹϾ��� �޾� ������.
	/// t�� 1.f ~ 0.f
	/// </summary>
	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		/// Q(t) = start - t * start  + t * end
		/// Q(t)�� ����ȭ���� �ϸ� �ȴ�.

		// Quaternion result{ q1 + (q2 - q1) * t };
		// return result.Normalized();

		return (q1 + (q2 - q1) * t).Normalized();
	}

	/// <summary>
	/// ����� ���� ����
	/// ����ȭ�� �� ���ʹϾ��� �޾� ������.
	/// t�� 1.f ~ 0.f
	/// </summary>
	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		/// Q(t) = 
		/// ( (sin(1 - t) * theta) / sin theta ) * start + 
		/// ( (sin(theta * t) ) / sin theta ) * end
		/// �׸��� ����ȭ

		Quaternion q1N{ q1 };
		Quaternion q2N{ q2 };

		// ������ ������� cos theta
		float cosTheta = q1N.Dot(q2N);

		// cos���� ������ ���ʹϾ� �ϳ��� ����ȭ �Ѵٴµ�
		// �� ������ �𸣰����� ��ư ã�ƺ� ����Ʈ���� �׸� �϶�� ��.
		// ���ʹϾ� ���� ������ 90���� �Ѿ�ϱ� ���� ���ϴ°� �� ª�� ��ζ� �׷��ɱ�
		// ��¥ ���� �𸣰���

		/// ��Ī ���
		/// �� ���ʹϾ� ������ ������ 90������ ũ�ٴ� ��
		/// ���� ���� ��, �� �� ���ȣ�� ���󰡰� �ȴ�.
		/// ���� ª�� ���ȣ�� ���󰡰� �ϱ� ���� ������ ���ϴ� ���ε�
		/// ���ʹϾ𿡼��� q�� -q�� ���� ȸ���� �ǹ��ϱ� ������ ȸ�� ��������� �ƹ��� ������ ����.
		/// ������ ���� ���������� ��ȣ�� �߿��ϴ�
		/// ���� ������ ���ȣ �󿡼� �� ���ʹϾ��� ���� ���ϰ� �մ� ���̱⿡
		/// ��ȣ�� ���� ������ �޶�����.
		if (cosTheta < 0.f)
		{
			q2N = -q2N;
			cosTheta = -cosTheta;
		}

		// cos Theta�� 1�� �Ѿ�� ū�ϳ���!! acos���� NaN�� ���� �����̴�!!!
		// �̰� ������ 1���� �� ����ߴ�
		if (cosTheta > 0.9999f)
		{
			// cosTheta�� 1�̰ų� -1�� ����
			// q1 = q2�ų� ���� �� �ݴ��� �ǹ�
			return Lerp(q1, q2, t);
		}

		// ���ʹϾ� ������ ������ ����
		float theta = std::acos(cosTheta);

		// ������ �� sin theta �̸� ����ص���
		float invSinTheta = 1 / std::sin(theta);

		// ���� ���� �����̴�
		float factorA{ std::sin((1.0f - t) * theta) * invSinTheta };
		float factorB{ std::sin(t * theta) * invSinTheta };

		// Quaternion result{ (factorA * q1N) + (factorB * q2N) };
		// return result.Normalized();
		return ((factorA * q1N) + (factorB * q2N)).Normalized();
	}

	/// <summary>
	/// ���Ϸ� ���� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Vector3D& _euler) noexcept
	{
		Vector3D eulerRad = _euler * (PI<float> / 180.0f);

		float cosX = std::cos(eulerRad.x * 0.5f);
		float sinX = std::sin(eulerRad.x * 0.5f);
		float cosY = std::cos(eulerRad.y * 0.5f);
		float sinY = std::sin(eulerRad.y * 0.5f);
		float cosZ = std::cos(eulerRad.z * 0.5f);
		float sinZ = std::sin(eulerRad.z * 0.5f);

		float cosYcosZ = cosY * cosZ;
		float sinYsinZ = sinY * sinZ;
		float cosYsinZ = cosY * sinZ;
		float sinYcosZ = sinY * cosZ;

		Quaternion q;
		q.w = cosX * cosYcosZ + sinX * sinYsinZ;
		q.x = sinX * cosYcosZ - cosX * sinYsinZ;
		q.y = cosX * sinYcosZ + sinX * cosYsinZ;
		q.z = cosX * cosYsinZ - sinX * sinYcosZ;

		return q;
	}

	/// <summary>
	/// �ఢ�� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Vector4D& _axisAngle) noexcept
	{
		float angleRad = ToRadian(_axisAngle.w);

		// ���ʹϾ� ȸ���� �� ��
		// ���ʹϾ��� �տ��� ���ϴ� �Ͱ� �ڿ��� ���ϴ� ���� �ٸ� ���ʹϾ��� Ư���� �����
		// ������ ������ ������ ������ġ�� ���δ� ��.
		// ���п� �Ǽ��δ� ������ �ǰ� ȸ���� �����ϰ� ��.
		float halfAngle = angleRad * 0.5f;
		float sinHalfAngle = std::sin(halfAngle);

		Vector3D axis = Vector3D(_axisAngle.x, _axisAngle.y, _axisAngle.z).Normalized();
		Quaternion q;
		q.w = std::cos(halfAngle);
		q.x = axis.x * sinHalfAngle;
		q.y = axis.y * sinHalfAngle;
		q.z = axis.z * sinHalfAngle;

		return q;
	}

	/// <summary>
	/// ȸ�� ����� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept
	{
		return Quaternion();
	}

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