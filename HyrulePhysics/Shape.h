#pragma once
#include <memory>
#include <vector>
#include "HyruleMath.h"

enum class ShapeType : int
{
	SPHERE = 0,
	BOX = 10,
	CAPSULE = 20,
	CONVEX = 30,
	PLANE = 40,
	MESH = 50,
};

namespace Hyrule
{
	struct Matrix3x3;
	struct Vector3D;

	namespace Physics
	{
		class Shape
		{
		public:
			Shape() noexcept = default;
			~Shape() noexcept = default;

		public:
			virtual std::vector<Vector3D> GetPoints() noexcept abstract;
		};
	
		class BoxShape : public Shape
		{
		public:
			BoxShape() noexcept;
			~BoxShape() noexcept = default;

		public:
			virtual std::vector<Vector3D> GetPoints() noexcept override;

		private:
			std::vector<Vector3D> points{
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, 0.5f },
				{ 0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, -0.5f },

				{ -0.5f, 0.5f, -0.5f }, { -0.5f, 0.5f, 0.5f },
				{-0.5f, 0.5f, -0.5f }, { 0.5f, 0.5f, 0.5f }
			};
			std::vector<size_t> index{
				1, 0, 3,		// 하
				1, 3, 2,

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
		};
	
		class PlaneShape : public Shape
		{
		public:
			PlaneShape() noexcept;
			~PlaneShape() noexcept = default;

		public:
			virtual std::vector<Vector3D> GetPoints() noexcept override;

		private:
			std::vector<Vector3D> points{
				{ -5.f, 0.f, -5.f }, { -5.f, 0.f, 5.f },
				{ 5.f, 0.f, 5.f }, { 5.f, 0.f, -5.f },
			};

			std::vector<size_t> index{
				0, 1, 2,
				0, 2, 3,
			};
		};

		class ConvexShape : public Shape
		{
		public:
			ConvexShape() noexcept;
			~ConvexShape() noexcept = default;

		public:
			virtual std::vector<Vector3D> GetPoints() noexcept override;

		private:
			std::vector<Vector3D> points;
			std::vector<size_t> index;
		};

		class Shapes
		{
		public:
			static void Initalize();

			static std::shared_ptr<BoxShape> boxShape;
			static std::shared_ptr<PlaneShape> planeShape;
			static std::vector<std::shared_ptr<ConvexShape>> convexShape;
		};
	
	}
}