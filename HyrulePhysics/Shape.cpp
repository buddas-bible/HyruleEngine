#include "Shape.h"

#include "PHYSICALLYOBJECT_INFO.h"

namespace Hyrule
{
	namespace Physics
	{
		void Shapes::Initalize()
		{
			boxShape = std::make_shared<BoxShape>();
			planeShape = std::make_shared<PlaneShape>();
		}

		std::shared_ptr<ConvexShape> Shapes::GetShape(const std::wstring& _name)
		{
			// auto itr = (Shapes::convexShapes).find(_name);

			// if (itr != (Shapes::convexShapes).end())
			// {
			// 	return itr->second;
			// }

			return nullptr;
		}

		std::shared_ptr<ConvexShape> Shapes::CreateConvexShape(const std::wstring& _name, SHAPE_INPO* _info)
		{
			return GetShape(_name);
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

		ConvexShape::ConvexShape(SHAPE_INPO* _info) noexcept : 
			points(_info->pPointArr, _info->pPointArr + _info->pPointArrSize),
			index(_info->pIndexArr, _info->pIndexArr + _info->pIndexArrSize)
		{}

		std::vector<Hyrule::Vector3D> ConvexShape::GetPoints() noexcept
		{
			return this->points;
		}

		std::shared_ptr<BoxShape> Shapes::boxShape{};
		std::shared_ptr<PlaneShape> Shapes::planeShape{};
		// std::vector<std::shared_ptr<ConvexShape>> convexShape{};
	}
}