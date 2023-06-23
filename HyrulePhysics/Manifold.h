#pragma once

namespace Hyrule
{
	class Collider;

	class Manifold
	{
	public:
		// Manifold() noexcept = default;
		Manifold(const Collider*& _A, const Collider*& _B) noexcept;
		// ~Manifold() noexcept = default;

	private:
		// 충돌 검사하는 두 콜라이더
		Collider* A;
		Collider* B;

		// 충돌의 노말 벡터
		// 충돌의 탄젠트 벡터
		// 충돌의 이선 벡터
		// 충돌의 깊이
		// 충돌 접점				// vector로 저장하면 vector의 size로 접점 개수 얻을 수 있음
		// 접점의 노말 벡터
	};
}