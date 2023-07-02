#include "AABB.h"



namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// 중심과 한 변의 길이를 받아서 AABB를 만듬
		/// </summary>
		AABB::AABB(const Vector3D& _center, float _length) noexcept :
			min(_center.x - _length / 2, _center.y - _length / 2, _center.z - _length / 2),
			max(_center.x + _length / 2, _center.y + _length / 2, _center.z + _length / 2)
		{

		}

		/// <summary>
		/// 최대 최소 값을 받아서 AABB를 만듬
		/// </summary>
		AABB::AABB(const Vector3D& _min, const Vector3D& _max) noexcept : 
			min(_min),
			max(_max)
		{

		}

		/// <summary>
		/// AABB 안에 점이 있는가?
		/// </summary>
		bool AABB::ContainsPoint(const Vector3D& _point) const noexcept
		{
			if (_point.x < this->min.x || _point.x > this->max.x)
				return false;
			if (_point.y < this->min.y || _point.y > this->max.y)
				return false;
			if (_point.z < this->min.z || _point.z > this->max.z)
				return false;

			return true;
		}

		/// <summary>
		/// 다른 AABB와 충돌 했는가?
		/// </summary>
		bool AABB::CollidingAABB(const AABB& _other) const noexcept
		{
			if (this->max.x < _other.min.x || this->min.x > _other.max.x)
				return false;
			if (this->max.y < _other.min.y || this->min.y > _other.max.y)
				return false;
			if (this->max.z < _other.min.z || this->min.z > _other.max.z)
				return false;

			return true;
		}
	}
}
