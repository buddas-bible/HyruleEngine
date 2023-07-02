#include "AABB.h"



namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// �߽ɰ� �� ���� ���̸� �޾Ƽ� AABB�� ����
		/// </summary>
		AABB::AABB(const Vector3D& _center, float _length) noexcept :
			center(_center),
			min(_center.x - _length / 2, _center.y - _length / 2, _center.z - _length / 2),
			max(_center.x + _length / 2, _center.y + _length / 2, _center.z + _length / 2),
			length(_length)
		{

		}

		/// <summary>
		/// �ִ� �ּ� ���� �޾Ƽ� AABB�� ����
		/// </summary>
		AABB::AABB(const Vector3D& _min, const Vector3D& _max) noexcept : 
			center((_max + _min) * 0.5f),
			min(_min),
			max(_max),
			length(_max.x - _min.x)
		{

		}

		/// <summary>
		/// AABB �ȿ� ���� �ִ°�?
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
		/// �ٸ� AABB�� �浹 �ߴ°�?
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
