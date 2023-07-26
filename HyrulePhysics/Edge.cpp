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

		Edge::Edge(const Edge& _edge) noexcept :
			vectorA(_edge.vectorA), vectorB(_edge.vectorB),
			index1(_edge.index1), index2(_edge.index2),
			direction(_edge.direction), normal(_edge.normal)
		{

		}

		Edge::Edge(Edge&& _edge) noexcept :
			vectorA(_edge.vectorA), vectorB(_edge.vectorB),
			index1(_edge.index1), index2(_edge.index2),
			direction(_edge.direction), normal(_edge.normal)
		{

		}

		Edge& Edge::operator=(const Edge& _other) noexcept
		{
			this->vectorA = _other.vectorA;
			this->vectorB = _other.vectorB;
			this->index1 = _other.index1;
			this->index2 = _other.index2;
			this->direction = _other.direction;
			this->normal = _other.normal;
		}

		Edge& Edge::operator=(Edge&& _other) noexcept
		{
			if (this != &_other)
			{
				this->vectorA = _other.vectorA;
				this->vectorB = _other.vectorB;
				this->index1 = _other.index1;
				this->index2 = _other.index2;
				this->direction = _other.direction;
				this->normal = _other.normal;
			}
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
				((this->vectorA == _other.vectorA) && (this->vectorB == _other.vectorB)) ||
				((this->vectorA == _other.vectorB) && (this->vectorB == _other.vectorA));
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