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

namespace Hyrule
{
	struct Matrix3x3;
	struct Vector3D;

	namespace Physics
	{
		struct SHAPE_INPO;

		class Shape
		{
		public:
			Shape() noexcept = default;
			~Shape() noexcept = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() noexcept abstract;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) noexcept abstract;
			virtual const std::vector<size_t>& GetIndies() noexcept abstract;
			virtual size_t GetType() noexcept abstract;
		};
	
		class BoxShape : public Shape
		{
		public:
			BoxShape() noexcept;
			~BoxShape() noexcept = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() noexcept override;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) noexcept override;
			virtual const std::vector<size_t>& GetIndies() noexcept override;
			virtual std::vector<Face> GetFaces(const Matrix4x4&) noexcept;
			virtual size_t GetType() noexcept override;

		private:
			std::vector<Vector3D> points{
				{ -0.5f, -0.5f, -0.5f }, { -0.5f, -0.5f, 0.5f },
				{ 0.5f, -0.5f, 0.5f }, { 0.5f, -0.5f, -0.5f },

				{ -0.5f, 0.5f, -0.5f }, { -0.5f, 0.5f, 0.5f },
				{ 0.5f, 0.5f, 0.5f }, { 0.5f, 0.5f, -0.5f }
			};
			std::vector<size_t> index{
				1, 3, 2,		// ��
				1, 0, 3,

				0, 4, 7,		// ��
				0, 7, 3,

				4, 5, 6,		// ��
				4, 6, 7,

				3, 7, 6,		// ��
				3, 6, 2,

				2, 6, 5,		// ��
				2, 5, 1,

				1, 5, 4,		// ��
				1, 4, 0,
			};

			std::vector<Face> faces;
		};
	
		class PlaneShape : public Shape
		{
		public:
			PlaneShape() noexcept;
			~PlaneShape() noexcept = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() noexcept override;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) noexcept override;
			virtual const std::vector<size_t>& GetIndies() noexcept override;
			virtual size_t GetType() noexcept override;

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
			ConvexShape() noexcept = default;
			ConvexShape(SHAPE_INPO*) noexcept;
			~ConvexShape() noexcept = default;

		public:
			virtual const std::vector<Vector3D>& GetPoints() noexcept override;
			virtual std::vector<Vector3D> GetPoints(const Matrix4x4&) noexcept override;
			virtual const std::vector<size_t>& GetIndies() noexcept override;
			virtual size_t GetType() noexcept override;

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