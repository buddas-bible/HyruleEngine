#pragma once

#include <cmath>
#include "HRVector.h"
#include "Quaternion.h"
#include "HRMatrix.h"
#include "HRConstant.h"

namespace Hyrule
{
	/// <summary>
	/// 라디안을 각도로 바꿈
	/// </summary>
	inline float ToDegree(const float _rad) noexcept
	{
		return _rad * (180.0f / PI<float>);
	}

	/// <summary>
	/// 각도를 라디안으로 바꿈
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
	/// 사원수 선형 보간
	/// 정규화된 두 쿼터니언을 받아 보간함.
	/// t는 1.f ~ 0.f
	/// </summary>
	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		/// Q(t) = start - t * start  + t * end
		/// Q(t)를 정규화까지 하면 된다.

		// Quaternion result{ q1 + (q2 - q1) * t };
		// return result.Normalized();

		return (q1 + (q2 - q1) * t).Normalized();
	}

	/// <summary>
	/// 사원수 구형 보간
	/// 정규화된 두 쿼터니언을 받아 보간함.
	/// t는 1.f ~ 0.f
	/// </summary>
	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
	{
		/// Q(t) = 
		/// ( (sin(1 - t) * theta) / sin theta ) * start + 
		/// ( (sin(theta * t) ) / sin theta ) * end
		/// 그리고 정규화

		Quaternion q1N{ q1 };
		Quaternion q2N{ q2 };

		// 내적의 결과값은 cos theta
		float cosTheta = q1N.Dot(q2N);

		// cos값이 음수면 쿼터니언 하나를 음수화 한다는데
		// 이 이유를 모르겠지만 암튼 찾아본 사이트에서 그리 하라고 함.
		// 쿼터니언 사이 각도가 90도가 넘어가니까 음수 취하는게 더 짧은 경로라서 그런걸까
		// 진짜 뭔지 모르겠음

		/// 서칭 결과
		/// 두 쿼터니언 사이의 각도가 90도보다 크다는 건
		/// 구형 보간 시, 더 긴 대원호를 따라가게 된다.
		/// 따라서 짧은 대원호를 따라가게 하기 위해 음수를 취하는 것인데
		/// 쿼터니언에서는 q와 -q는 같은 회전을 의미하기 때문에 회전 결과에서는 아무런 영향이 없다.
		/// 하지만 구형 보간에서는 부호가 중요하다
		/// 구형 보간은 대원호 상에서 두 쿼터니언의 점을 구하고 잇는 것이기에
		/// 부호에 따라 방향이 달라진다.
		if (cosTheta < 0.f)
		{
			q2N = -q2N;
			cosTheta = -cosTheta;
		}

		// cos Theta가 1이 넘어가면 큰일난다!! acos에서 NaN을 띄우기 때문이다!!!
		// 이거 때문에 1쿼터 때 고생했다
		if (cosTheta > 0.9999f)
		{
			// cosTheta가 1이거나 -1인 경우는
			// q1 = q2거나 서로 정 반대라는 의미
			return Lerp(q1, q2, t);
		}

		// 쿼터니언 사이의 각도를 구함
		float theta = std::acos(cosTheta);

		// 어차피 쓸 sin theta 미리 계산해두자
		float invSinTheta = 1 / std::sin(theta);

		// 구형 보간 공식이다
		float factorA{ std::sin((1.0f - t) * theta) * invSinTheta };
		float factorB{ std::sin(t * theta) * invSinTheta };

		// Quaternion result{ (factorA * q1N) + (factorB * q2N) };
		// return result.Normalized();
		return ((factorA * q1N) + (factorB * q2N)).Normalized();
	}

	/// <summary>
	/// 오일러 각을 쿼터니언으로 바꿈
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
	/// 축각을 쿼터니언으로 바꿈
	/// </summary>
	Quaternion ToQuaternion(const Vector4D& _axisAngle) noexcept
	{
		float angleRad = ToRadian(_axisAngle.w);

		// 쿼터니언 회전을 할 때
		// 쿼터니언을 앞에서 곱하는 것과 뒤에서 곱하는 것이 다른 쿼터니언의 특성을 살려서
		// 각도를 반으로 나눠서 샌드위치로 감싸는 것.
		// 덕분에 실수부는 유지가 되고 회전이 가능하게 됨.
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
	/// 회전 행렬을 쿼터니언으로 바꿈
	/// </summary>
	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept
	{
		return Quaternion();
	}

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