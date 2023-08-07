#pragma once
#include "HyruleMath.h"


/// <summary>
/// AABB
/// 
/// 중심과 길이만 넘겨주면 최대 최소를 알아서 계산해 줬으면 좋겠음.
/// 그리고 다른 AABB와의 계산도 편리하게 하기 위해서.
/// </summary>
namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class AABB
		{
		public:
			AABB() = default;
			AABB(const AABB&) noexcept = default;
			AABB(AABB&&) noexcept = default;
			AABB(const Vector3D& _center, float _length) noexcept;
			AABB(const Vector3D& _min, const Vector3D& _max) noexcept;
			AABB& operator=(const AABB&) noexcept = default;
			AABB& operator=(AABB&&) noexcept = default;
			~AABB() noexcept = default;

		public:
			Vector3D min;
			Vector3D max;

		public:
			Vector3D GetCenter() const noexcept;
			bool ContainsPoint(const Vector3D&) const noexcept;
			bool TestRay(const Vector3D&, const Vector3D&) const noexcept;
			bool Overlap(const AABB&) const noexcept;
			bool Contains(const AABB&);
		};

		float Volume(const AABB&);
		Vector3D Min(const Vector3D&, const Vector3D&);
		Vector3D Max(const Vector3D&, const Vector3D&);
		AABB Union(const AABB&, const AABB&);
	}
}

