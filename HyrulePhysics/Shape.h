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
			virtual Vector3D GetCenterOfMess() abstract;
			virtual	Matrix3x3 GetInertiaTensor(float) abstract;
			virtual void CalculateCenterOfMessAndInertiaTensor(float) abstract;
		};
	}
}