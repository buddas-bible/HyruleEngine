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
		{}

		/// <summary>
		/// 최대 최소 값을 받아서 AABB를 만듬
		/// </summary>
		AABB::AABB(const Vector3D& _min, const Vector3D& _max) noexcept : 
			min(_min),
			max(_max)
		{}

		Vector3D AABB::GetCenter() const noexcept
		{
			return (min + max) * 0.5f;
		}

		/// <summary>
		/// AABB 안에 점이 있는가?
		/// </summary>
		bool AABB::ContainsPoint(const Vector3D& _point) const noexcept
		{
			if ((this->min.x > _point.x) || (_point.x > this->max.x)) return false;
			if ((this->min.y > _point.y) || (_point.y > this->max.y)) return false;
			if ((this->min.z > _point.z) || (_point.z > this->max.z)) return false;

			return true;
		}

		/// <summary>
		/// 다른 AABB와 충돌 했는가?
		/// </summary>
		bool AABB::Overlap(const AABB& _other) const noexcept
		{
			if ((this->max.x < _other.min.x) || (_other.max.x < this->min.x)) return false;
			if ((this->max.y < _other.min.y) || (_other.max.y < this->min.y)) return false;
			if ((this->max.z < _other.min.z) || (_other.max.z < this->min.z)) return false;

 			return true;
		}

		/// <summary>
		/// other의 AABB를 완전히 포함하는가?
		/// </summary>
		bool AABB::Contains(const AABB& _other)
		{
			return 
				(this->min.x <= _other.min.x) &&
				(this->max.x >= _other.max.x) &&
				(this->min.y <= _other.min.y) &&
				(this->max.y >= _other.max.y) &&
				(this->min.z <= _other.min.z) &&
				(this->max.z >= _other.max.z);
		}

		/// <summary>
		/// AABB가 Ray와 충돌 했는가?
		/// </summary>
		bool AABB::TestRay(const Vector3D& _from, const Vector3D& _to) const noexcept
		{
			Vector3D direction = _to - _from;
			Vector3D invDir = Vector3D(1.0f / direction.x, 1.0f / direction.y, 1.0f / direction.z);

			float tMin = (min.x - _from.x) * invDir.x;
			float tMax = (max.x - _from.x) * invDir.x;

			if (tMin > tMax) 
				std::swap(tMin, tMax);

			float tYMin = (min.y - _from.y) * invDir.y;
			float tYMax = (max.y - _from.y) * invDir.y;

			if (tYMin > tYMax) 
				std::swap(tYMin, tYMax);

			if ((tMin > tYMax) || (tYMin > tMax)) 
				return false;

			if (tYMin > tMin) 
				tMin = tYMin;

			if (tYMax < tMax) 
				tMax = tYMax;

			float tZMin = (min.z - _from.z) * invDir.z;
			float tZMax = (max.z - _from.z) * invDir.z;

			if (tZMin > tZMax) 
				std::swap(tZMin, tZMax);

			if ((tMin > tZMax) || (tZMin > tMax)) 
				return false;

			return true;
		}

		float Volume(const AABB& _A)
		{
			Vector3D d{ _A.max - _A.min };
			return d.x * d.y * d.z;
		}

		Vector3D Min(const Vector3D& _A, const Vector3D& _B)
		{
			return
				Vector3D(
					std::min(_A.x, _B.x),
					std::min(_A.y, _B.y),
					std::min(_A.z, _B.z)
				);
		}

		Vector3D Max(const Vector3D& _A, const Vector3D& _B)
		{
			return
				Vector3D(
					std::max(_A.x, _B.x),
					std::max(_A.y, _B.y),
					std::max(_A.z, _B.z)
				);
		}

		AABB Union(const AABB& _A, const AABB& _B)
		{
			return AABB(Min(_A.min, _B.min), Max(_A.max, _B.max));
		}
	}
}
