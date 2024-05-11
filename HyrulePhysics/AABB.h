#pragma once
#include "HyruleMath.h"


/// <summary>
/// AABB
/// 
/// 중심과 길이만 넘겨주면 최대 최소를 알아서 계산해 줬으면 좋겠음.
/// 그리고 다른 AABB와의 계산도 편리하게 하기 위해서.
/// </summary>
namespace hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class AABB
		{
		public:
			AABB() = default;
			AABB(const AABB&) = default;
			AABB(AABB&&) = default;
			AABB(const Vector3D& _center, float _length);
			AABB(const Vector3D& _min, const Vector3D& _max);
			AABB& operator=(const AABB&) = default;
			AABB& operator=(AABB&&) = default;
			~AABB() = default;

		public:
			Vector3D min;
			Vector3D max;

		public:
			Vector3D GetCenter() const;
			bool ContainsPoint(const Vector3D&) const;
			bool TestRay(const Vector3D&, const Vector3D&) const;
			bool TestSegment(const Vector3D& _from, const Vector3D& _to, const float _length) const;
			bool Overlap(const AABB&) const;
			bool Contains(const AABB&);
		};

		float Volume(const AABB&);
		Vector3D Min(const Vector3D&, const Vector3D&);
		Vector3D Max(const Vector3D&, const Vector3D&);
		AABB Union(const AABB&, const AABB&);
	}
}

