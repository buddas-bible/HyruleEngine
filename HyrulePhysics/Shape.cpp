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
			return nullptr;
		}

		std::shared_ptr<ConvexShape> Shapes::CreateConvexShape(const std::wstring& _name, SHAPE_INPO* _info)
		{
			return GetShape(_name);
		}


		BoxShape::BoxShape() noexcept : Shape()
		{
			for (auto i = 0; i < index.size(); i += 3)
			{
				faces.push_back(
				{ 
						points[index[i]], 
						points[index[i + 1]], 
						points[index[i + 2]], 
						index[i], 
						index[i + 1] , 
						index[i + 2]
					 }
				);
			}
		}

		const std::vector<Vector3D>& BoxShape::GetPoints() noexcept
		{
			return this->points;
		}

		std::vector<Vector3D> BoxShape::GetPoints(const Matrix4x4& _matrix) noexcept
		{
			std::vector<Vector3D> point;

			for (auto& p : points)
			{
				point.push_back(p * _matrix);
			}

			return point;
		}

		const std::vector<size_t>& BoxShape::GetIndies() noexcept
		{
			return this->index;
		}

		std::vector<Face> BoxShape::GetFaces(const Matrix4x4& _matrix) noexcept
		{
			std::vector<Vector3D> temp;

			for (auto i = 0; i < points.size(); i++)
			{
				temp.push_back(points[i] * _matrix);
			}

			std::vector<Face> tempfaces;

			for (auto i = 0; i < index.size(); i += 3)
			{
				tempfaces.push_back(
					{
							temp[index[i]],
							temp[index[i + 1]],
							temp[index[i + 2]],
							index[i],
							index[i + 1] ,
							index[i + 2]
					}
				);
			}

			return tempfaces;
		}


		PlaneShape::PlaneShape() noexcept : Shape()
		{
			for (auto i = 0; i < index.size(); i += 3)
			{
				faces.push_back(
					{
							points[index[i]],
							points[index[i + 1]],
							points[index[i + 2]],
							index[i],
							index[i + 1] ,
							index[i + 2]
					}
				);
			}
		}

		const std::vector<Vector3D>& PlaneShape::GetPoints() noexcept
		{
			return this->points;
		}

		std::vector<Vector3D> PlaneShape::GetPoints(const Matrix4x4& _matrix) noexcept
		{
			std::vector<Vector3D> point;

			for (auto& p : points)
			{
				point.push_back(p * _matrix);
			}

			return point;
		}

		const std::vector<size_t>& PlaneShape::GetIndies() noexcept
		{
			return this->index;
		}


		ConvexShape::ConvexShape(SHAPE_INPO* _info) noexcept :
			points(_info->pPointArr, _info->pPointArr + _info->pPointArrSize),
			index(_info->pIndexArr, _info->pIndexArr + _info->pIndexArrSize)
		{
			for (auto i = 0; i < index.size(); i += 3)
			{
				faces.push_back(
					{
							points[index[i]],
							points[index[i + 1]],
							points[index[i + 2]],
							index[i],
							index[i + 1] ,
							index[i + 2]
					}
				);
			}
		}

		const std::vector<Vector3D>& ConvexShape::GetPoints() noexcept
		{
			return this->points;
		}

		std::vector<Hyrule::Vector3D> ConvexShape::GetPoints(const Matrix4x4& _matrix) noexcept
		{
			std::vector<Vector3D> point;

			for (auto& p : points)
			{
				point.push_back(p * _matrix);
			}

			return point;
		}

		const std::vector<size_t>& ConvexShape::GetIndies() noexcept
		{
			return this->index;
		}

		std::shared_ptr<BoxShape> Shapes::boxShape{};
		std::shared_ptr<PlaneShape> Shapes::planeShape{};
		// std::vector<std::shared_ptr<ConvexShape>> convexShape{};
	}
}