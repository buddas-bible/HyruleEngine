#pragma once
#include <vector>

#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Collider;

		/// <summary>
		/// 두 콜라이더의 충돌 정보를저장하는 클래스
		/// </summary>
		class Manifold
		{
		public:
			// Manifold() noexcept = default;
			Manifold(Collider*& _A, Collider*& _B) noexcept;
			~Manifold() noexcept = default;

		private:
			// 충돌 검사하는 두 콜라이더
			Collider* A;
			Collider* B;

			// 충돌 정보
			Hyrule::Vector3D normal;						// 충돌의 노말 벡터
			Hyrule::Vector3D tangent;						// 충돌의 탄젠트 벡터
															// 충돌의 이선 벡터
			float depth;									// 충돌의 깊이
			std::vector<Hyrule::Vector3D> contactPoints;	// 충돌 접점				// vector로 저장하면 vector의 size로 접점 개수 얻을 수 있음
			Hyrule::Vector3D contactNormal;					// 접점의 노말 벡터

			float friction;

			bool collided;

		public:
			bool IsColliding();

			Vector3D GetNormal() const noexcept;
			void SetNormal(const Vector3D& _normal) noexcept;

			Vector3D GetTangent() const noexcept;
			void SetTangent(const Vector3D& _tangent) noexcept;

			Vector3D GetContactNormal() const noexcept;
			void SetContactNormal(const Vector3D& _contactNormal) noexcept;

			float GetDepth() const noexcept;
			void SetDepth(float _depth) noexcept;

			const std::vector<Vector3D>& GetContactPoints() const;
			void AddContactPoint(const Vector3D& point);

			std::vector<Vector3D> simplex;
			std::vector<size_t> index;

		private:
			/// <summary>
			/// 매니폴드가 GJK를 가지고 있는 것이 아닌
			/// GJK의 반환이 매니폴드가 되어야할 것 같음.
			/// 충돌하면 매니폴드를 반환
			/// 충돌하지 않으면 nullptr을 반환하는 방식으로 해서
			/// 
			/// 아니면 그냥 GJK랑 EPA를 함수 객체로 만들어볼까
			/// </summary>
			void CheckCollision();

			void CollisionEvent();

		};
	}
}