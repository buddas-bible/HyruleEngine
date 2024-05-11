#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "HyruleMath.h"
#include "Face.h"

enum class ShapeType : size_t
{
	SPHERE = 0,
	BOX = 1,
	CAPSULE = 2,
	CONVEX = 3,
	PLANE = 4,
	MESH = 5,
};

namespace hyrule
{
	struct Matrix3x3;
	struct Vector3D;

	namespace Physics
	{
		struct SHAPE_INPO;

		class Shape
		{
		public:
			Shape() = default;
			~Shape() = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() abstract;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) abstract;
			virtual const std::vector<size_t>& GetIndies() abstract;
			virtual size_t GetType() abstract;
		};
	
		class BoxShape : public Shape
		{
		public:
			BoxShape();
			~BoxShape() = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() override;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) override;
			virtual const std::vector<size_t>& GetIndies() override;
			virtual std::vector<Face> GetFaces(const Matrix4x4&);
			virtual size_t GetType() override;

		private:
			std::vector<Vector3D> points{
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, 0.5f },
				{ 0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, -0.5f },

				{ -0.5f, 0.5f, -0.5f }, { -0.5f, 0.5f, 0.5f },
				{ 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, -0.5f }
			};
			std::vector<size_t> index{
				1, 3, 2,		// 하
				1, 0, 3,

				0, 4, 7,		// 전
				0, 7, 3,

				4, 5, 6,		// 상
				4, 6, 7,

				3, 7, 6,		// 우
				3, 6, 2,

				2, 6, 5,		// 후
				2, 5, 1,

				1, 5, 4,		// 좌
				1, 4, 0,
			};

			std::vector<Face> faces;
		};
	
		class PlaneShape : public Shape
		{
		public:
			PlaneShape();
			~PlaneShape() = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() override;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) override;
			virtual const std::vector<size_t>& GetIndies() override;
			virtual size_t GetType() override;

		private:
			std::vector<Vector3D> points{
				{ -5.f, 0.f, -5.f }, { -5.f, 0.f, 5.f },
				{ 5.f, 0.f, 5.f }, { 5.f, 0.f, -5.f },
			};

			std::vector<size_t> index{
				0, 3, 2,
				0, 2, 1,
			};

			std::vector<Face> faces;
		};

		class ConvexShape : public Shape
		{
		public:
			ConvexShape() = default;
			ConvexShape(SHAPE_INPO*);
			~ConvexShape() = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() override;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) override;
			virtual const std::vector<size_t>& GetIndies() override;
			virtual size_t GetType() override;

		private:
			std::vector<Vector3D> points;
			std::vector<size_t> index;
			std::vector<Face> faces;
		};

		class Shapes
		{
		public:
			static void Initalize();
			static std::shared_ptr<ConvexShape> GetShape(const std::wstring&);
			static std::shared_ptr<ConvexShape> CreateConvexShape(const std::wstring& _name, SHAPE_INPO* _info);

			static std::shared_ptr<BoxShape> boxShape;
			static std::shared_ptr<PlaneShape> planeShape;
			// static std::map<std::wstring, std::shared_ptr<ConvexShape>> convexShapes;
		};
	
	}
}