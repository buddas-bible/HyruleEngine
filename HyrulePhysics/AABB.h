#pragma once
#include "HyruleMath.h"


/// <summary>
/// AABB
/// 
/// �߽ɰ� ���̸� �Ѱ��ָ� �ִ� �ּҸ� �˾Ƽ� ����� ������ ������.
/// �׸��� �ٸ� AABB���� ��굵 ���ϰ� �ϱ� ���ؼ�.
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

