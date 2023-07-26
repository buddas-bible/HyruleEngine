#include <cmath>

#include "Vector4D.h"
#include "Quaternion.h"
#include "Vector3D.h"
#include "Matrix3x3.h"
#include "Matrix4x4.h"

#include "HRMathFunc.h"

namespace Hyrule
{
	/// <summary>
	/// ���Ϸ����� ��Ʈ������ ��ȯ
	/// </summary>
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

	/// <summary>
	/// ������ ��Ʈ������ ��ȯ
	/// </summary>
	Matrix4x4 ToScaleMatrix(const Vector3D& _scl) noexcept
	{
		return Matrix4x4
		{
			_scl.x,		0.f,		0.f,		0.f,
			0.f,		_scl.y,		0.f,		0.f,
			0.f,		0.f,		_scl.z,		0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}

	/// <summary>
	/// ������ ��Ʈ������ ��ȯ
	/// </summary>
	Matrix4x4 ToScaleMatrix(const float _scl) noexcept
	{
		return Matrix4x4
		{
			_scl,		0.f,		0.f,		0.f,
			0.f,		_scl,		0.f,		0.f,
			0.f,		0.f,		_scl,		0.f,
			0.f,		0.f,		0.f,		1.f
		};
	}

	/// <summary>
	/// Ʈ������ ��Ʈ������ ��ȯ
	/// </summary>
	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const Vector3D& _scl) noexcept
	{
		return ToScaleMatrix(_scl) * ToMatrix4(_rot) * ToTranslateMatrix(_pos);
	}

	Matrix4x4 ToTransformMatrix(const Vector3D& _pos, const Quaternion& _rot, const float _scl) noexcept
	{
		return ToScaleMatrix(_scl) * ToMatrix4(_rot) * ToTranslateMatrix(_pos);
	}


	Vector3D DecomposPosition(const Matrix4x4& _mat) noexcept
	{
		return Vector3D(_mat.e30, _mat.e31, _mat.e32);
	}

	Quaternion DecomposRotation(const Matrix4x4& _mat) noexcept
	{
		Vector3D scl{ DecomposScale(_mat) };

		Matrix1x3 row00{ _mat.e00, _mat.e01, _mat.e02 };
		row00 /= scl.x;
		Matrix1x3 row01{ _mat.e10, _mat.e11, _mat.e12 };
		row01 /= scl.y;
		Matrix1x3 row02{ _mat.e20, _mat.e21, _mat.e22 };
		row02 /= scl.z;

		return ToQuaternion({ row00 , row01, row02 });
	}

	Vector3D DecomposScale(const Matrix4x4& _mat) noexcept
	{
		return Vector3D(
			Vector3D(_mat.e00, _mat.e01, _mat.e02).Length(), 
			Vector3D(_mat.e10, _mat.e11, _mat.e12).Length(), 
			Vector3D(_mat.e20, _mat.e21, _mat.e22).Length()
		);
	}

	/// <summary>
	/// Ʈ������ ��� ����?
	/// </summary>
	void Decompose(const Matrix4x4& _matrix, Vector3D& _pos, Quaternion& _rot, Vector3D& _scl) noexcept
	{
		// ���� ����� ������ ���
		_pos.x = _matrix.m[3].e00;
		_pos.y = _matrix.m[3].e01;
		_pos.z = _matrix.m[3].e02;

		// ���� ����� �� ������ ũ�Ⱑ ������ ��
		_scl.x = Vector3D(_matrix.e00, _matrix.e10, _matrix.e20).Length();
		_scl.y = Vector3D(_matrix.e01, _matrix.e11, _matrix.e21).Length();
		_scl.z = Vector3D(_matrix.e02, _matrix.e12, _matrix.e22).Length();

		// ����ȭ�ؼ� ȸ������ ����
		Matrix4x4 rotationMatrix = _matrix;
		rotationMatrix.m[0] /= _scl.x;
		rotationMatrix.m[1] /= _scl.y;
		rotationMatrix.m[2] /= _scl.z;

		// ȸ�� ����� ���ʹϾ����� ��ȯ
		_rot = ToQuaternion(rotationMatrix);
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

	Vector3D VectorRotateFromQuaternion(const Vector3D& _vec, const Quaternion& _q) noexcept
	{
		Quaternion q_con{ _q.Conjugate() };
		Quaternion vec{ 0.f, _vec.x, _vec.y, _vec.z };

		Quaternion result{ _q * vec * q_con };

		return Vector3D(result.x, result.y, result.z);
	}

	/// <summary>
	/// ���͸� ��ǥ�ϴ� ���ͷ� ��ȯ�ϱ� ���� ���ʹϾ��� ��ȯ
	/// </summary>
	Quaternion RotateVectorToVectorQuaternion(const Vector3D& _from, const Vector3D& _to) noexcept
	{
		Vector3D normalizedFrom = _from.Normalized();
		Vector3D normalizedTo = _to.Normalized();

		Vector3D rotationAxis = normalizedFrom.Cross(normalizedTo);

		float rotationAngle = std::acosf(normalizedFrom.Dot(normalizedTo));

		return ToQuaternion(rotationAxis, rotationAngle);
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
		Vector3D axis = Vector3D(_axisAngle.x, _axisAngle.y, _axisAngle.z).Normalized();
		float halfAngle = _axisAngle.w * 0.5f;
		float sinhalf = std::sinf(halfAngle);
		float coshalf = std::cosf(halfAngle);

		return Quaternion
		{
			coshalf,
			axis.x* sinhalf,
			axis.y* sinhalf,
			axis.z* sinhalf
		};
	}

	Quaternion ToQuaternion(const Vector3D& _axis, float _angle) noexcept
	{
		Vector3D axis = _axis.Normalized();
		float halfAngle = _angle * 0.5f;
		float sinhalf = std::sinf(halfAngle);
		float coshalf = std::cosf(halfAngle);

		return Quaternion
		(
			coshalf,
			axis.x * sinhalf,
			axis.y * sinhalf,
			axis.z * sinhalf
		);
	}
	
	/// <summary>
	/// ȸ�� ����� ���ʹϾ����� �ٲ�
	/// </summary>
	Quaternion ToQuaternion(const Matrix3x3& _rotMatrix) noexcept
	{
		Quaternion quaternion;

		float trace = _rotMatrix.e00 + _rotMatrix.e11 + _rotMatrix.e22;

		if (trace > 0.0f) {
			float s = 0.5f / std::sqrt(trace + 1.0f);
			quaternion.w = 0.25f / s;
			quaternion.x = (_rotMatrix.e21 - _rotMatrix.e12) * s;
			quaternion.y = (_rotMatrix.e02 - _rotMatrix.e20) * s;
			quaternion.z = (_rotMatrix.e10 - _rotMatrix.e01) * s;
		}
		else
		{
			if (_rotMatrix.e00 > _rotMatrix.e11 && _rotMatrix.e00 > _rotMatrix.e22)
			{
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e00 - _rotMatrix.e11 - _rotMatrix.e22);
				quaternion.w = (_rotMatrix.e21 - _rotMatrix.e12) / s;
				quaternion.x = 0.25f * s;
				quaternion.y = (_rotMatrix.e01 + _rotMatrix.e10) / s;
				quaternion.z = (_rotMatrix.e02 + _rotMatrix.e20) / s;
			}
			else if (_rotMatrix.e11 > _rotMatrix.e22) {
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e11 - _rotMatrix.e00 - _rotMatrix.e22);
				quaternion.w = (_rotMatrix.e02 - _rotMatrix.e20) / s;
				quaternion.x = (_rotMatrix.e01 + _rotMatrix.e10) / s;
				quaternion.y = 0.25f * s;
				quaternion.z = (_rotMatrix.e12 + _rotMatrix.e21) / s;
			}
			else {
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e22 - _rotMatrix.e00 - _rotMatrix.e11);
				quaternion.w = (_rotMatrix.e10 - _rotMatrix.e01) / s;
				quaternion.x = (_rotMatrix.e02 + _rotMatrix.e20) / s;
				quaternion.y = (_rotMatrix.e12 + _rotMatrix.e21) / s;
				quaternion.z = 0.25f * s;
			}
		}

		return quaternion;
	}

	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept
	{
		Quaternion quaternion;

		float trace = _rotMatrix.e00 + _rotMatrix.e11 + _rotMatrix.e22;

		if (trace > 0.0f) {
			float s = 0.5f / std::sqrt(trace + 1.0f);
			quaternion.w = 0.25f / s;
			quaternion.x = (_rotMatrix.e21 - _rotMatrix.e12) * s;
			quaternion.y = (_rotMatrix.e02 - _rotMatrix.e20) * s;
			quaternion.z = (_rotMatrix.e10 - _rotMatrix.e01) * s;
		}
		else
		{
			if (_rotMatrix.e00 > _rotMatrix.e11 && _rotMatrix.e00 > _rotMatrix.e22)
			{
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e00 - _rotMatrix.e11 - _rotMatrix.e22);
				quaternion.w = (_rotMatrix.e21 - _rotMatrix.e12) / s;
				quaternion.x = 0.25f * s;
				quaternion.y = (_rotMatrix.e01 + _rotMatrix.e10) / s;
				quaternion.z = (_rotMatrix.e02 + _rotMatrix.e20) / s;
			}
			else if (_rotMatrix.e11 > _rotMatrix.e22) {
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e11 - _rotMatrix.e00 - _rotMatrix.e22);
				quaternion.w = (_rotMatrix.e02 - _rotMatrix.e20) / s;
				quaternion.x = (_rotMatrix.e01 + _rotMatrix.e10) / s;
				quaternion.y = 0.25f * s;
				quaternion.z = (_rotMatrix.e12 + _rotMatrix.e21) / s;
			}
			else {
				float s = 2.0f * std::sqrt(1.0f + _rotMatrix.e22 - _rotMatrix.e00 - _rotMatrix.e11);
				quaternion.w = (_rotMatrix.e10 - _rotMatrix.e01) / s;
				quaternion.x = (_rotMatrix.e02 + _rotMatrix.e20) / s;
				quaternion.y = (_rotMatrix.e12 + _rotMatrix.e21) / s;
				quaternion.z = 0.25f * s;
			}
		}

		return quaternion;
	}

	/// <summary>
	/// ���ʹϾ��� ���Ϸ������� �ٲ�
	/// </summary>
	Vector3D ToEuler(const Quaternion& _q) noexcept
	{
		const float x2 = _q.x * _q.x;
		const float y2 = _q.y * _q.y;
		const float z2 = _q.z * _q.z;
		const float w2 = _q.w * _q.w;

		Vector3D euler;

		// Roll (Z-axis rotation)
		float sinRoll = 2.0f * (_q.w * _q.x + _q.y * _q.z);
		float cosRoll = w2 - x2 - y2 + z2;
		euler.x = std::atan2f(sinRoll, cosRoll);

		// Pitch (X-axis rotation)
		float sinPitch = 2.0f * (_q.w * _q.y - _q.z * _q.x);
		euler.y = std::asinf(sinPitch);

		// Yaw (Y-axis rotation)
		float sinYaw = 2.0f * (_q.w * _q.z + _q.x * _q.y);
		float cosYaw = w2 + x2 - y2 - z2;
		euler.z = std::atan2f(sinYaw, cosYaw);

		return euler;
	}

	/// <summary>
	/// ���ʹϾ��� �ఢ���� �ٲ�
	/// </summary>
	Vector4D ToAxisAngle(const Quaternion& _q) noexcept
	{
		float squaredLength = _q.LengthSquare();

		if (squaredLength < Epsilon)
		{
			// Quaternion represents no rotation, return zero axis and angle
			return Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
		}

		float inverseLength = 1.0f / std::sqrt(squaredLength);
		float angle = 2.0f * std::acos(_q.w);
		float sinAngle = std::sqrt(1.0f - _q.w * _q.w) * inverseLength;

		return Vector4D(_q.x * inverseLength, _q.y * inverseLength, _q.z * inverseLength, angle);
	}

	/// <summary>
	/// ���ʹϾ��� ��ķ� �ٲ�
	/// </summary>
	Matrix3x3 ToMatrix3(const Quaternion& _q) noexcept
	{
		Matrix3x3 matrix;

		const float w2 = _q.w * _q.w;
		const float x2 = _q.x * _q.x;
		const float y2 = _q.y * _q.y;
		const float z2 = _q.z * _q.z;
		const float xy = _q.x * _q.y;
		const float xz = _q.x * _q.z;
		const float yz = _q.y * _q.z;
		const float wx = _q.w * _q.x;
		const float wy = _q.w * _q.y;
		const float wz = _q.w * _q.z;

		matrix.e00 = 1.0f - 2.0f * (y2 + z2);
		matrix.e01 = 2.0f * (xy + wz);
		matrix.e02 = 2.0f * (xz - wy);

		matrix.e10 = 2.0f * (xy - wz);
		matrix.e11 = 1.0f - 2.0f * (x2 + z2);
		matrix.e12 = 2.0f * (yz + wx);

		matrix.e20 = 2.0f * (xz + wy);
		matrix.e21 = 2.0f * (yz - wx);
		matrix.e22 = 1.0f - 2.0f * (x2 + y2);

		return matrix;
	}

	Matrix4x4 ToMatrix4(const Quaternion& _q) noexcept
	{
		Matrix4x4 matrix;

		const float w2 = _q.w * _q.w;
		const float x2 = _q.x * _q.x;
		const float y2 = _q.y * _q.y;
		const float z2 = _q.z * _q.z;
		const float xy = _q.x * _q.y;
		const float xz = _q.x * _q.z;
		const float yz = _q.y * _q.z;
		const float wx = _q.w * _q.x;
		const float wy = _q.w * _q.y;
		const float wz = _q.w * _q.z;

		matrix.e00 = 1.0f - 2.0f * (y2 + z2);
		matrix.e01 = 2.0f * (xy + wz);
		matrix.e02 = 2.0f * (xz - wy);
		matrix.e03 = 0.0f;

		matrix.e10 = 2.0f * (xy - wz);
		matrix.e11 = 1.0f - 2.0f * (x2 + z2);
		matrix.e12 = 2.0f * (yz + wx);
		matrix.e13 = 0.0f;

		matrix.e20 = 2.0f * (xz + wy);
		matrix.e21 = 2.0f * (yz - wx);
		matrix.e22 = 1.0f - 2.0f * (x2 + y2);
		matrix.e23 = 0.0f;

		matrix.e30 = 0.0f;
		matrix.e31 = 0.0f;
		matrix.e32 = 0.0f;
		matrix.e33 = 1.0f;

		return matrix;
	}

	/// <summary>
	/// �ఢ�� ��ķ� �ٲ�
	/// </summary>
	Matrix3x3 ToMatrix3(const Vector3D& _axis, const float _angle) noexcept
	{
		float cos = std::cos(_angle);
		float sin = std::sin(_angle);
		float x = _axis.x;
		float y = _axis.y;
		float z = _axis.z;

		return Matrix3x3(
			cos + x * x * (1 - cos),
			x * y * (1 - cos) - z * sin,
			x * z * (1 - cos) + y * sin,

			y * x * (1 - cos) + z * sin,
			cos + y * y * (1 - cos),
			y * z * (1 - cos) - x * sin,

			z * x * (1 - cos) - y * sin,
			z * y * (1 - cos) + x * sin,
			cos + z * z * (1 - cos)
		);
	}

	Matrix4x4 ToMatrix4(const Vector3D& _axis, const float _angle) noexcept
	{
		float cos = std::cos(_angle);
		float sin = std::sin(_angle);
		float x = _axis.x;
		float y = _axis.y;
		float z = _axis.z;

		return Matrix4x4(
			cos + x * x * (1 - cos),
			x * y * (1 - cos) - z * sin,
			x * z * (1 - cos) + y * sin,
			0.f,

			y * x * (1 - cos) + z * sin,
			cos + y * y * (1 - cos),
			y * z * (1 - cos) - x * sin,
			0.f,

			z * x * (1 - cos) - y * sin,
			z * y * (1 - cos) + x * sin,
			cos + z * z * (1 - cos),
			0.f,

			0.f,
			0.f,
			0.f,
			1.f
		);
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