#pragma once

enum class ShapeType : int
{
	SPHERE,
	BOX,
	CAPSULE,
	POLYHEDRON,
	MESH,
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
			virtual ~Shape() noexcept = default;

		protected:
			ShapeType type;

		public:
			virtual int GetShapeType() abstract;
			virtual float GetLength() abstract;
		};
	}
}