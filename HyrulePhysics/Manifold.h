#pragma once
#include "HRVector.h"


namespace Hyrule
{
	class Collider;

	/// <summary>
	/// 두 콜라이더의 충돌 정보를저장하는 클래스
	/// </summary>
	class Manifold
	{
	public:
		// Manifold() noexcept = default;
		Manifold(const Collider*& _A, const Collider*& _B) noexcept;
		// ~Manifold() noexcept = default;

	private:
		// 충돌 검사하는 두 콜라이더
		Collider const* A;
		Collider const* B;

		// 충돌 정보
		Vector3D normal;			// 충돌의 노말 벡터
		Vector3D tangent;			// 충돌의 탄젠트 벡터
									// 충돌의 이선 벡터
		float depth;				// 충돌의 깊이
		// std::vector<Vector3D> contactPoints;	// 충돌 접점				// vector로 저장하면 vector의 size로 접점 개수 얻을 수 있음
		Vector3D contactNormal;		// 접점의 노말 벡터

	public:
		Vector3D GetNormal() const noexcept;
		void SetNormal(const Vector3D& _normal) noexcept;

		Vector3D GetTangent() const noexcept;
		void SetTangent(const Vector3D& _tangent) noexcept;

		Vector3D GetContactNormal() const noexcept;
		void SetContactNormal(const Vector3D& _contactNormal) noexcept;

		float GetDepth() const noexcept;
		void SetDepth(float _depth) noexcept;

		// const std::vector<Vector3D>& GetContactPoints() const;
		// void AddContactPoint(const Vector3& point);

	};
}