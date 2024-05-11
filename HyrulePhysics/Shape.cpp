#include "Shape.h"

#include "PHYSICALLYOBJECT_INFO.h"

namespace hyrule
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


		BoxShape::BoxShape() : Shape()
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

		const std::vector<Vector3D>& BoxShape::GetPoints()
		{
			return this->points;
		}

		std::vector<Vector3D> BoxShape::GetPoints(const Matrix4x4& _matrix)
		{
			std::vector<Vector3D> point;

			for (auto& p : points)
			{
				point.push_back(p * _matrix);
			}

			return point;
		}

		const std::vector<size_t>& BoxShape::GetIndies()
		{
			return this->index;
		}

		std::vector<Face> BoxShape::GetFaces(const Matrix4x4& _matrix)
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


		size_t BoxShape::GetType()
		{
			return (size_t)ShapeType::BOX;
		}

		PlaneShape::PlaneShape() : Shape()
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

		const std::vector<Vector3D>& PlaneShape::GetPoints()
		{
			return this->points;
		}

		std::vector<Vector3D> PlaneShape::GetPoints(const Matrix4x4& _matrix)
		{
			std::vector<Vector3D> point;

			for (auto& p : points)
			{
				point.push_back(p * _matrix);
			}

			return point;
		}

		const std::vector<size_t>& PlaneShape::GetIndies()
		{
			return this->index;
		}


		size_t PlaneShape::GetType()
		{
			return (size_t)ShapeType::PLANE;
		}

		ConvexShape::ConvexShape(SHAPE_INPO* _info) :
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

		const std::vector<Vector3D>& ConvexShape::GetPoints()
		{
			return this->points;
		}

		std::vector<hyrule::Vector3D> ConvexShape::GetPoints(const Matrix4x4& _matrix)
		{
			std::vector<Vector3D> point;

			for (auto& p : points)
			{
				point.push_back(p * _matrix);
			}

			return point;
		}

		const std::vector<size_t>& ConvexShape::GetIndies()
		{
			return this->index;
		}


		size_t ConvexShape::GetType()
		{
			return (size_t)ShapeType::CONVEX;
		}

		std::shared_ptr<BoxShape> Shapes::boxShape{};
		std::shared_ptr<PlaneShape> Shapes::planeShape{};
		// std::vector<std::shared_ptr<ConvexShape>> convexShape{};
	}
}