#include "HRMathFunc.h"

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

	Matrix4x4 ToTranslateMatrix(const Vector3D& _euler) noexcept
	{
		return Matrix4x4
		{
			1.f,		0.f,		0.f,		0.f,
			0.f,		1.f,		0.f,		0.f,
			0.f,		0.f,		1.f,		0.f,
			_euler.x,	_euler.y,	_euler.z,	1.f
		};
	}

	Matrix4x4 ToScaleMatrix(const Vector3D& _euler) noexcept
	{
		return Matrix4x4
		{
			_euler.x,	0.f,		0.f,		0.f,
			0.f,		_euler.y,	0.f,		0.f,
			0.f,		0.f,		_euler.z,	0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept
	{
		return ToScaleMatrix(_scl) * _rot.ToMatrix() * ToTranslateMatrix(_pos);
	}

	/// <summary>
	/// Ʈ������ ��� ����?
	/// </summary>
	void Decompose(Vector4D& _pos, Quaternion& _rot, Vector4D& _scl, const Matrix4x4& _matrix) noexcept
	{
		// transformTM = S * R * T
		Matrix4x4 temp{ _matrix };

		// �̵��� ���� ��
		_pos.m = _matrix.m[3].m;
		temp.m[3] = { 0.f, 0.f, 0.f, 1.f };
		
		// ������ ���� �� ������ ũ��� �ϸ� ��
		// temp = temp.Transpose();				// �̺κе� ��ġ�ϸ� ���� �� ���������
		_scl.x = Vector3D{ _matrix.m[0].e[0], _matrix.m[1].e[0], _matrix.m[2].e[0] }.Length();
		_scl.y = Vector3D{ _matrix.m[0].e[1], _matrix.m[1].e[1], _matrix.m[2].e[1] }.Length();
		_scl.z = Vector3D{ _matrix.m[0].e[2], _matrix.m[1].e[2], _matrix.m[2].e[2] }.Length();
		_scl.w = 0.f;

		// ȸ�� ��ĸ� ����� ���� ������ �� ������
		temp.m[0] /= _scl.x;
		temp.m[1] /= _scl.y;
		temp.m[2] /= _scl.z;

		_rot = ToQuaternion(temp);
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
		Vector3D eulerRad = ( _euler * (PI<float> / 180.0f) ) * 0.5f;

		float cosX = std::cos(eulerRad.x);
		float sinX = std::sin(eulerRad.x);
		float cosY = std::cos(eulerRad.y);
		float sinY = std::sin(eulerRad.y);
		float cosZ = std::cos(eulerRad.z);
		float sinZ = std::sin(eulerRad.z);

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
	Quaternion ToQuaternion(const Matrix3x3& _rotMatrix) noexcept
	{
		Quaternion quaternion;

		// 	float trace = _rotMatrix.e[0][0] + _rotMatrix.e[1][1] + _rotMatrix.e[2][2];
		// 
		// 	if (trace > 0.0f)
		// 	{
		// 		float s = 0.5f / sqrtf(trace + 1.0f);
		// 		quaternion.w = 0.25f / s;
		// 		quaternion.x = (_rotMatrix.e[2][1] - _rotMatrix.e[1][2]) * s;
		// 		quaternion.y = (_rotMatrix.e[0][2] - _rotMatrix.e[2][0]) * s;
		// 		quaternion.z = (_rotMatrix.e[1][0] - _rotMatrix.e[0][1]) * s;
		// 	}
		// 	else
		// 	{
		// 		if (_rotMatrix.e[0][0] > _rotMatrix.e[1][1] && _rotMatrix.e[0][0] > _rotMatrix.e[2][2])
		// 		{
		// 			float s = 2.0f * sqrtf(1.0f + _rotMatrix.e[0][0] - _rotMatrix.e[1][1] - _rotMatrix.e[2][2]);
		// 			quaternion.w = (_rotMatrix.e[2][1] - _rotMatrix.e[1][2]) / s;
		// 			quaternion.x = 0.25f * s;
		// 			quaternion.y = (_rotMatrix.e[0][1] + _rotMatrix.e[1][0]) / s;
		// 			quaternion.z = (_rotMatrix.e[0][2] + _rotMatrix.e[2][0]) / s;
		// 		}
		// 		else if (_rotMatrix.e[1][1] > _rotMatrix.e[2][2])
		// 		{
		// 			float s = 2.0f * sqrtf(1.0f + _rotMatrix.e[1][1] - _rotMatrix.e[0][0] - _rotMatrix.e[2][2]);
		// 			quaternion.w = (_rotMatrix.e[0][2] - _rotMatrix.e[2][0]) / s;
		// 			quaternion.x = (_rotMatrix.e[0][1] + _rotMatrix.e[1][0]) / s;
		// 			quaternion.y = 0.25f * s;
		// 			quaternion.z = (_rotMatrix.e[1][2] + _rotMatrix.e[2][1]) / s;
		// 		}
		// 		else
		// 		{
		// 			float s = 2.0f * sqrtf(1.0f + _rotMatrix.e[2][2] - _rotMatrix.e[0][0] - _rotMatrix.e[1][1]);
		// 			quaternion.w = (_rotMatrix.e[1][0] - _rotMatrix.e[0][1]) / s;
		// 			quaternion.x = (_rotMatrix.e[0][2] + _rotMatrix.e[2][0]) / s;
		// 			quaternion.y = (_rotMatrix.e[1][2] + _rotMatrix.e[2][1]) / s;
		// 			quaternion.z = 0.25f * s;
		// 		}
		// 	}

		return quaternion;
	}


	Quaternion ToQuaternion(const Vector3D& _axis, float _angle) noexcept
	{
		Vector3D axis = _axis.Normalized();
		float half = _angle * 0.5f;
		float sinhalf = std::sinf(half);
		float coshalf = std::cosf(half);

		return Quaternion
		(
			coshalf,
			axis.x * sinhalf,
			axis.y * sinhalf,
			axis.z * sinhalf
		);
	}


	Quaternion RotateVectorToVectorQuaternion(const Vector3D& _from, const Vector3D& _to)
	{
		Vector3D normalizedFrom = _from.Normalized();
		Vector3D normalizedTo = _to.Normalized();

		Vector3D rotationAxis = normalizedFrom.Cross(normalizedTo);

		float rotationAngle = std::acosf(normalizedFrom.Dot(normalizedTo));

		return ToQuaternion(rotationAxis, rotationAngle);
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