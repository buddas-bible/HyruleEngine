#include "Shape.h"

namespace Hyrule
{
	namespace Physics
	{
		void Shapes::Initalize()
		{

		}

		BoxShape::BoxShape() noexcept : Shape()
		{}

		std::vector<Hyrule::Vector3D> BoxShape::GetPoints() noexcept
		{
			return this->points;
		}

		PlaneShape::PlaneShape() noexcept : Shape()
		{}

		std::vector<Hyrule::Vector3D> PlaneShape::GetPoints() noexcept
		{
			return this->points;
		}

		ConvexShape::ConvexShape() noexcept : Shape()
		{}

		std::vector<Hyrule::Vector3D> ConvexShape::GetPoints() noexcept
		{
			return this->points;
		}
	}
}