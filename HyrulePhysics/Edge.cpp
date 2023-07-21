#include "Edge.h"


namespace Hyrule
{
	namespace Physics
	{
		Edge::Edge(const Vector3D& _A, const Vector3D& _B, size_t _ia, size_t _ib) noexcept :
			vectorA(_A), vectorB(_B), index1(_ia), index2(_ib), direction()
		{
			this->Initialze();
		}

		void Edge::Initialze() noexcept
		{
			if (this->vectorA != this->vectorB)
			{
				this->direction = (this->vectorB - this->vectorA).Normalized();
			}
		}

		void Edge::SetNormal(const Vector3D& _edgeNormal) noexcept
		{
			this->normal = _edgeNormal;
		}

		bool Edge::operator==(const Edge& _other) noexcept
		{
			return 
				(this->index1 == _other.index2 && this->index2 == _other.index1) || 
				(this->index1 == _other.index1 && this->index2 == _other.index2);
		}

		float Edge::GetLength() const noexcept
		{
			return (vectorA - vectorB).Length();
		}

		float Edge::GetLengthSquare() const noexcept
		{
			return (vectorA - vectorB).LengthSquare();
		}
	}
}