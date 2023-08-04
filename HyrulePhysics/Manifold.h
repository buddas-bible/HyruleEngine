#pragma once
#include <vector>

#include "HyruleMath.h"
#include "Simplex.h"

namespace Hyrule
{
	namespace Physics
	{
		class Collider;
		class RigidBody;

		/// <summary>
		/// 두 콜라이더의 충돌 정보를저장하는 클래스
		/// </summary>
		class Manifold
		{
		public:
			// Manifold() noexcept = default;
			Manifold(Collider*& _A, Collider*& _B) noexcept;
			Manifold(const Manifold&) noexcept = default;
			Manifold(Manifold&&) noexcept = default;
			~Manifold() noexcept = default;
			Manifold& operator=(const Manifold&) = default;
			Manifold& operator=(Manifold&&) = default;

		private:
			// 충돌 검사하는 두 콜라이더
			Collider* A;
			Collider* B;

			// 충돌 정보
			Vector3D normal;								// 충돌의 노말 벡터

			float depth;									// 충돌의 깊이
			std::vector<Vector3D> contactPoints;			// 충돌 접점

			Simplex simplex{};

		public:
			RigidBody* RigidBodyA();
			RigidBody* RigidBodyB();
			Vector3D PositionA();
			Vector3D PositionB();

		public:
			void Apply();

			void SetSimplex(const Simplex& _simplex);
			Simplex& GetSimplex();
			void Clear();

			Collider* GetColliderA();
			Collider* GetColliderB();
			void SetColliderA(Collider*);
			void SetColliderB(Collider*);

			Vector3D GetNormal() const noexcept;
			void SetNormal(const Vector3D& _normal) noexcept;

			Vector3D GetContactNormal() const noexcept;
			void SetContactNormal(const Vector3D& _contactNormal) noexcept;

			float GetDepth() const noexcept;
			void SetDepth(float _depth) noexcept;

			const std::vector<Vector3D>& GetContactPoints() const;
			void AddContactPoint(const Vector3D& point);
		};
	}
}