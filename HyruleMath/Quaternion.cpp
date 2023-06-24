#include "Quaternion.h"

#include <cmath>
#include <utility>

#include "HRMathFunc.h"
#include "HRMatrix.h"
#include "HRVector.h"
#include "HRConstant.h"

namespace Hyrule
{
	Quaternion::Quaternion(float _w, float _x, float _y, float _z) noexcept
		:
		e{ _w, _x, _y, _z }
	{

	}

	Quaternion::operator Matrix1x4() noexcept
	{
		return Matrix1x4{ x, y, z, w };
	}

	Quaternion::operator Vector4D() noexcept
	{
		return Vector4D{ x, y, z, w };
	}

	Quaternion Quaternion::Identity() noexcept
	{
		return Quaternion{ 1.f, 0.f, 0.f, 0.f };
	}

	float Quaternion::Length() const noexcept
	{
		return powf(x * x + y * y + z * z + w * w, 0.5f);
	}

	float Quaternion::LengthSquare() const noexcept
	{
		return x * x + y * y + z * z + w * w;
	}

	float Quaternion::FastInvSqrt(float number) const noexcept
	{
		long i;
		float x2, y;
		const float threehalfs = 1.5f;

		x2 = number * 0.5f;
		y = number;
		i = *(long*)&y;
		//	i = 0x5f3759df - (i >> 1);
		i = 0x5f375a86 - (i >> 1);
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));
		//	y = y * ( threehalfs - ( x2 * y * y ) ); // 2nd iteration, this can be removed

		return y;
	}

	/// <summary>
	/// 사원수 내적
	/// </summary>
	float Quaternion::Dot(const Quaternion& other) const noexcept
	{
		return (this->w * other.w) + (this->x * other.x) + (this->y * other.y) + (this->z * other.z);
	}

	/// <summary>
	/// 사원수 켤레
	/// </summary>
	Quaternion Quaternion::Conjugate() const noexcept
	{
		return Quaternion{ w, -x, -y, -z };
	}

	/// <summary>
	/// 사원수 역수
	/// </summary>
	Quaternion Quaternion::Inverse() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0.0f)
		{
			return *this;
		}

		float invSqrt = 1 / temp;
			
		return Quaternion
		(
			w * invSqrt,
			-x * invSqrt, 
			-y * invSqrt, 
			-z * invSqrt
		);
	}

	Quaternion& Quaternion::Normalize() noexcept
	{
		float temp = LengthSquare();

		if (temp == 0.0f)
		{
			return *this;
		}

		float invSqrt = FastInvSqrt(temp);

		w *= invSqrt;
		x *= invSqrt;
		y *= invSqrt;
		z *= invSqrt;

		return *this;
	}
	
	Quaternion Quaternion::Normalized() const noexcept
	{
		float temp = LengthSquare();

		if (temp == 0)
		{
			return Quaternion(*this);
		}

		float invSqrt = FastInvSqrt(temp);

		return Quaternion
		(
			w * invSqrt,
			x * invSqrt, 
			y * invSqrt, 
			z * invSqrt
		);
	}

	/// <summary>
	/// 오일러 각으로 변환
	/// </summary>
	Vector3D Quaternion::ToEuler() const noexcept
	{
		const float x2 = x * x;
		const float y2 = y * y;
		const float z2 = z * z;
		const float w2 = w * w;

		Vector3D euler;

		// Roll (X-axis rotation)
		const float sinRoll = 2.0f * (w * x + y * z);
		const float cosRoll = w2 - x2 - y2 + z2;
		euler.x = std::atan2(sinRoll, cosRoll);

		// Pitch (Y-axis rotation)
		const float sinPitch = 2.0f * (w * y - z * x);
		euler.y = std::asin(sinPitch);

		// Yaw (Z-axis rotation)
		const float sinYaw = 2.0f * (w * z + x * y);
		const float cosYaw = w2 + x2 - y2 - z2;
		euler.z = std::atan2(sinYaw, cosYaw);

		return euler;
	}

	/// <summary>
	/// 축각으로 변환
	/// </summary>
	Vector4D Quaternion::ToAxisAngle() const noexcept
	{
		float squaredLength = LengthSquare();

		if (squaredLength < Epsilon)
		{
			// Quaternion represents no rotation, return zero axis and angle
			return Vector4D(0.0f, 0.0f, 0.0f, 0.0f);
		}

		float inverseLength = 1.0f / std::sqrt(squaredLength);
		float angle = 2.0f * std::acos(w);
		float sinAngle = std::sqrt(1.0f - w * w) * inverseLength;

		return Vector4D(x * inverseLength, y * inverseLength, z * inverseLength, angle);
	}

	/// <summary>
	/// 회전 행렬로 변환
	/// </summary>
	Matrix4x4 Quaternion::ToMatrix() const noexcept
	{
		Matrix4x4 matrix;

		const float w2 = w * w;
		const float x2 = x * x;
		const float y2 = y * y;
		const float z2 = z * z;
		const float xy = x * y;
		const float xz = x * z;
		const float yz = y * z;
		const float wx = w * x;
		const float wy = w * y;
		const float wz = w * z;

		matrix.e00 = 1.0f - 2.0f * (y2 + z2);
		matrix.e01 = 2.0f * (xy - wz);
		matrix.e02 = 2.0f * (xz + wy);
		matrix.e03 = 0.0f;

		matrix.e10 = 2.0f * (xy + wz);
		matrix.e11 = 1.0f - 2.0f * (x2 + z2);
		matrix.e12 = 2.0f * (yz - wx);
		matrix.e13 = 0.0f;

		matrix.e20 = 2.0f * (xz - wy);
		matrix.e21 = 2.0f * (yz + wx);
		matrix.e22 = 1.0f - 2.0f * (x2 + y2);
		matrix.e23 = 0.0f;

		matrix.e30 = 0.0f;
		matrix.e31 = 0.0f;
		matrix.e32 = 0.0f;
		matrix.e33 = 1.0f;

		return matrix;

	}

	/// <summary>
	/// 사원수 덧셈
	/// </summary>
	Quaternion& Quaternion::operator+=(const Quaternion& other) noexcept
	{
		this->w += other.w;
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;

		return *this;
	}

	/// <summary>
	/// 사원수 뺄셈
	/// </summary>
	Quaternion& Quaternion::operator-=(const Quaternion& other) noexcept
	{
		this->w -= other.w;
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;

		return *this;
	}

	Quaternion Quaternion::operator+(const Quaternion& other) const noexcept
	{
		return Quaternion
		(
			this->w + other.w, 
			this->x + other.x,
			this->y + other.y,
			this->z + other.z
		);
	}

	Quaternion Quaternion::operator-(const Quaternion& other) const noexcept
	{
		return Quaternion
		(
			this->w - other.w,
			this->x - other.x,
			this->y - other.y,
			this->z - other.z
		);
	}

	Quaternion Quaternion::operator-() const noexcept
	{
		return Quaternion
		(
			-this->w,
			-this->x,
			-this->y,
			-this->z
		);
	}

	/// <summary>
	/// 사원수 곱셈
	/// </summary>
	Quaternion& Quaternion::operator*=(const Quaternion& other) noexcept
	{
		float newW = 
			this->w * other.w - 
			this->x * other.x - 
			this->y * other.y - 
			this->z * other.z;

		float newX = 
			this->w * other.x + 
			this->x * other.w +
			this->y * other.z -
			this->z * other.y;

		float newY = 
			this->w * other.y - 
			this->x * other.z + 
			this->y * other.w + 
			this->z * other.x;

		float newZ = 
			this->w * other.z + 
			this->x * other.y - 
			this->y * other.x + 
			this->z * other.w;

		w = newW;
		x = newX;
		y = newY;
		z = newZ;

		return *this;
	}

	/// <summary>
	/// 사원수 나눗셈
	/// </summary>
	Quaternion& Quaternion::operator/=(const Quaternion& other) noexcept
	{
		Quaternion conjugate = other.Conjugate();
		float temp = other.LengthSquare();

		/// 사원수 나눗셈은 해당 사원수의 켤레를 곱하고
		*this *= conjugate;

		/// 크기의 제곱을 나눈 것과 같다.
		*this /= temp;

		return *this;
	}

	Quaternion Quaternion::operator*(const Quaternion& other) const noexcept
	{
		Quaternion result = *this;
		result *= other;
		return result;
	}

	Quaternion Quaternion::operator/(const Quaternion& other) const noexcept
	{
		Quaternion result = *this;
		result /= other;
		return result;
	}
	
	/// <summary>
	/// 사원수 스칼라 곱셈
	/// </summary>
	Quaternion& Quaternion::operator*=(const float n) noexcept
	{
		this->w *= n;
		this->x *= n;
		this->y *= n;
		this->z *= n;

		return *this;
	}

	/// <summary>
	/// 사원수 스칼라 나눗셈
	/// </summary>
	Quaternion& Quaternion::operator/=(const float n) noexcept
	{
		float invN = 1.0f / n;

		this->w *= invN;
		this->x *= invN;
		this->y *= invN;
		this->z *= invN;

		return *this;
	}

	Quaternion Quaternion::operator*(const float n) const noexcept
	{
		Quaternion result(*this);

		result *= n;

		return result;
	}

	Quaternion Quaternion::operator/(const float n) const noexcept
	{
		Quaternion result(*this);

		result /= n;

		return result;
	}

	bool Quaternion::operator==(const Quaternion& other) const noexcept
	{
		return (this->w == other.w && this->x == other.x && this->y == other.y && this->z == other.z);
	}

	Quaternion& operator*=(const float n, Quaternion& other) noexcept
	{
		other.w *= n;
		other.x *= n;
		other.y *= n;
		other.z *= n;

		return other;
	}

	Quaternion& operator/=(const float n, Quaternion& other) noexcept
	{
		float invN = 1.0f / n;

		other.w *= invN;
		other.x *= invN;
		other.y *= invN;
		other.z *= invN;

		return other;
	}

	Quaternion operator*(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		result *= n;

		return result;
	}

	Quaternion operator/(const float n, const Quaternion& other) noexcept
	{
		Quaternion result(other);

		result /= n;

		return result;
	}

// 	/// <summary>
// 	/// 사원수 선형 보간
// 	/// 정규화된 두 쿼터니언을 받아 보간함.
// 	/// t는 1.f ~ 0.f
// 	/// </summary>
// 	Quaternion Lerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept
// 	{
// 		/// Q(t) = start - t * start  + t * end
// 		/// Q(t)를 정규화까지 하면 된다.
// 
// 		// Quaternion result{ q1 + (q2 - q1) * t };
// 		// return result.Normalized();
// 
// 		return (q1 + (q2 - q1) * t).Normalized();
// 	}
// 
// 	/// <summary>
// 	/// 사원수 구형 보간
// 	/// 정규화된 두 쿼터니언을 받아 보간함.
// 	/// t는 1.f ~ 0.f
// 	/// </summary>
// 	Quaternion Slerp(const Quaternion& q1, const Quaternion& q2, float t) noexcept 
// 	{
// 		/// Q(t) = 
// 		/// ( (sin(1 - t) * theta) / sin theta ) * start + 
// 		/// ( (sin(theta * t) ) / sin theta ) * end
// 		/// 그리고 정규화
// 
// 		Quaternion q1N{ q1 };
// 		Quaternion q2N{ q2 };
// 
// 		// 내적의 결과값은 cos theta
// 		float cosTheta = q1N.Dot(q2N);
// 
// 		// cos값이 음수면 쿼터니언 하나를 음수화 한다는데
// 		// 이 이유를 모르겠지만 암튼 찾아본 사이트에서 그리 하라고 함.
// 		// 쿼터니언 사이 각도가 90도가 넘어가니까 음수 취하는게 더 짧은 경로라서 그런걸까
// 		// 진짜 뭔지 모르겠음
// 
// 		/// 서칭 결과
// 		/// 두 쿼터니언 사이의 각도가 90도보다 크다는 건
// 		/// 구형 보간 시, 더 긴 대원호를 따라가게 된다.
// 		/// 따라서 짧은 대원호를 따라가게 하기 위해 음수를 취하는 것인데
// 		/// 쿼터니언에서는 q와 -q는 같은 회전을 의미하기 때문에 회전 결과에서는 아무런 영향이 없다.
// 		/// 하지만 구형 보간에서는 부호가 중요하다
// 		/// 구형 보간은 대원호 상에서 두 쿼터니언의 점을 구하고 잇는 것이기에
// 		/// 부호에 따라 방향이 달라진다.
// 		if (cosTheta < 0.f)
// 		{
// 			q2N = -q2N;
// 			cosTheta = -cosTheta;
// 		}
// 
// 		// cos Theta가 1이 넘어가면 큰일난다!! acos에서 NaN을 띄우기 때문이다!!!
// 		// 이거 때문에 1쿼터 때 고생했다
// 		if (cosTheta > 0.9999f)
// 		{
// 			// cosTheta가 1이거나 -1인 경우는
// 			// q1 = q2거나 서로 정 반대라는 의미
// 			return Lerp(q1, q2, t);
// 		}
// 
// 		// 쿼터니언 사이의 각도를 구함
// 		float theta = std::acos(cosTheta);
// 
// 		// 어차피 쓸 sin theta 미리 계산해두자
// 		float invSinTheta = 1 / std::sin(theta);
// 
// 		// 구형 보간 공식이다
// 		float factorA{ std::sin((1.0f - t) * theta) * invSinTheta };
// 		float factorB{ std::sin(t * theta) * invSinTheta };
// 
// 		// Quaternion result{ (factorA * q1N) + (factorB * q2N) };
// 		// return result.Normalized();
// 		return ((factorA * q1N) + (factorB * q2N)).Normalized();
// 	}
// 
// 	/// <summary>
// 	/// 오일러 각을 쿼터니언으로 바꿈
// 	/// </summary>
// 	Quaternion ToQuaternion(const Vector3D& _euler) noexcept
// 	{
// 		Vector3D eulerRad = _euler * (PI<float> / 180.0f);
// 
// 		float cosX = std::cos(eulerRad.x * 0.5f);
// 		float sinX = std::sin(eulerRad.x * 0.5f);
// 		float cosY = std::cos(eulerRad.y * 0.5f);
// 		float sinY = std::sin(eulerRad.y * 0.5f);
// 		float cosZ = std::cos(eulerRad.z * 0.5f);
// 		float sinZ = std::sin(eulerRad.z * 0.5f);
// 
// 		float cosYcosZ = cosY * cosZ;
// 		float sinYsinZ = sinY * sinZ;
// 		float cosYsinZ = cosY * sinZ;
// 		float sinYcosZ = sinY * cosZ;
// 
// 		Quaternion q;
// 		q.w = cosX * cosYcosZ + sinX * sinYsinZ;
// 		q.x = sinX * cosYcosZ - cosX * sinYsinZ;
// 		q.y = cosX * sinYcosZ + sinX * cosYsinZ;
// 		q.z = cosX * cosYsinZ - sinX * sinYcosZ;
// 
// 		return q;
// 	}
// 
// 	/// <summary>
// 	/// 축각을 쿼터니언으로 바꿈
// 	/// </summary>
// 	Quaternion ToQuaternion(const Vector4D& _axisAngle) noexcept
// 	{
// 		float angleRad = ToRadian(_axisAngle.w);
// 
// 		// 쿼터니언 회전을 할 때
// 		// 쿼터니언을 앞에서 곱하는 것과 뒤에서 곱하는 것이 다른 쿼터니언의 특성을 살려서
// 		// 각도를 반으로 나눠서 샌드위치로 감싸는 것.
// 		// 덕분에 실수부는 유지가 되고 회전이 가능하게 됨.
// 		float halfAngle = angleRad * 0.5f;
// 		float sinHalfAngle = std::sin(halfAngle);
// 
// 		Vector3D axis = Vector3D(_axisAngle.x, _axisAngle.y, _axisAngle.z).Normalized();
// 		Quaternion q;
// 		q.w = std::cos(halfAngle);
// 		q.x = axis.x * sinHalfAngle;
// 		q.y = axis.y * sinHalfAngle;
// 		q.z = axis.z * sinHalfAngle;
// 
// 		return q;
// 	}
// 
// 	/// <summary>
// 	/// 회전 행렬을 쿼터니언으로 바꿈
// 	/// </summary>
// 	Quaternion ToQuaternion(const Matrix4x4& _rotMatrix) noexcept
// 	{
// 		return Quaternion();
// 	}
}