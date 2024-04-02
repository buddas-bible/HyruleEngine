#include "AABB.h"



namespace Hyrule
{
	namespace Physics
	{
		/// <summary>
		/// 중심과 한 변의 길이를 받아서 AABB를 만듬
		/// </summary>
		AABB::AABB(const Vector3D& _center, float _length) :
			min(_center.x - _length / 2, _center.y - _length / 2, _center.z - _length / 2),
			max(_center.x + _length / 2, _center.y + _length / 2, _center.z + _length / 2)
		{}

		/// <summary>
		/// 최대 최소 값을 받아서 AABB를 만듬
		/// </summary>
		AABB::AABB(const Vector3D& _min, const Vector3D& _max) : 
			min(_min),
			max(_max)
		{}

		Vector3D AABB::GetCenter() const
		{
			return (min + max) * 0.5f;
		}

		/// <summary>
		/// AABB 안에 점이 있는가?
		/// </summary>
		bool AABB::ContainsPoint(const Vector3D& _point) const
		{
			if ((this->min.x > _point.x) || (_point.x > this->max.x)) return false;
			if ((this->min.y > _point.y) || (_point.y > this->max.y)) return false;
			if ((this->min.z > _point.z) || (_point.z > this->max.z)) return false;

			return true;
		}

		/// <summary>
		/// 다른 AABB와 충돌 했는가?
		/// </summary>
		bool AABB::Overlap(const AABB& _other) const
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
		bool AABB::TestRay(const Vector3D& _from, const Vector3D& _to) const
		{
			Vector3D invDir(1.0f / (_to.x - _from.x), 1.0f / (_to.y - _from.y), 1.0f / (_to.z - _from.z));
			float tMin, tMax, tYMin, tYMax, tZMin, tZMax;

			tMin = (min.x - _from.x) * invDir.x;
			tMax = (max.x - _from.x) * invDir.x;

			if (invDir.x < 0.0f) 
				std::swap(tMin, tMax);

			tYMin = (min.y - _from.y) * invDir.y;
			tYMax = (max.y - _from.y) * invDir.y;

			if (invDir.y < 0.0f) 
				std::swap(tYMin, tYMax);

			tMin = std::max(tMin, tYMin);
			tMax = std::min(tMax, tYMax);

			if (tMin > tMax) 
				return false;

			tZMin = (min.z - _from.z) * invDir.z;
			tZMax = (max.z - _from.z) * invDir.z;

			if (invDir.z < 0.0f) 
				std::swap(tZMin, tZMax);

			tMin = std::max(tMin, tZMin);
			tMax = std::min(tMax, tZMax);

			return !(tMin > tMax);
		}


		bool AABB::TestSegment(const Vector3D& _from, const Vector3D& _to, const float _length) const
		{
			Vector3D end = _from + _to * _length;
			Vector3D invDir(1.0f / (_to.x * _length), 1.0f / (_to.y * _length), 1.0f / (_to.z * _length));

			float tmin = 0.0f;
			float tmax = _length;

			for (int i = 0; i < 3; ++i) 
			{
				float t1 = (min.e[i] - _from.e[i]) * invDir.e[i];
				float t2 = (max.e[i] - _from.e[i]) * invDir.e[i];

				if (invDir.e[i] < 0.0f) 
					std::swap(t1, t2);

				tmin = std::max(tmin, t1);
				tmax = std::min(tmax, t2);

				if (tmax < tmin) 
					return false;
			}

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
