#pragma once
#include "HyruleMath.h"


/// <summary>
/// AABB
/// 
/// �߽ɰ� ���̸� �Ѱ��ָ� �ִ� �ּҸ� �˾Ƽ� ����� ������ ������.
/// �׸��� �ٸ� AABB���� ��굵 ���ϰ� �ϱ� ���ؼ�.
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

