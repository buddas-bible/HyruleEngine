#pragma once

enum class ShapeType : int
{
	SPHERE,
	BOX,
	CAPSULE,
	CONVEX,
};

namespace Hyrule
{
	struct Matrix3x3;

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
			virtual Matrix3x3 GetInertiaTensor() abstract;
		};
	}
}