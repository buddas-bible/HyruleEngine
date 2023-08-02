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
			AABB() = delete;
			AABB(const Vector3D& _center, float _length) noexcept;
			AABB(const Vector3D& _min, const Vector3D& _max) noexcept;
			~AABB() noexcept = default;

		public:
			const Vector3D center;
			const Vector3D min;
			const Vector3D max;
			const float length;

		public:
			bool ContainsPoint(const Vector3D&) const noexcept;
			bool CollidingRay(const Vector3D&, const Vector3D&) const noexcept;
			bool CollidingAABB(const AABB&) const noexcept;
		};

		float Area(const AABB&);
		Vector3D Min(const Vector3D&, const Vector3D&);
		Vector3D Max(const Vector3D&, const Vector3D&);
		AABB Union(const AABB&, const AABB&);
	}
}

