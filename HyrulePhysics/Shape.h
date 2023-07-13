#pragma once

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

		protected:
			ShapeType type;

		public:
			virtual int GetShapeType() abstract;
			virtual float GetLength() abstract;
		};
	}
}