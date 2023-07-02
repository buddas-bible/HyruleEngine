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

		private:
			Vector3D min;
			Vector3D max;

		public:
			bool ContainsPoint(const Vector3D&) const noexcept;
			bool CollidingAABB(const AABB&) const noexcept;
		};
	}
}

