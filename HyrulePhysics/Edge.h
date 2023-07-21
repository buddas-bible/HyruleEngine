#pragma once
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		struct Edge
		{
			Edge() noexcept = default;
			Edge(const Vector3D&, const Vector3D&, size_t, size_t) noexcept;
			~Edge() noexcept = default;

			void Initialze() noexcept;
			float GetLength() const noexcept;
			float GetLengthSquare() const noexcept;
			void SetNormal(const Vector3D&) noexcept;

			Vector3D vectorA;
			Vector3D vectorB;

			size_t index1;
			size_t index2;

			Vector3D direction;
			Vector3D normal;

			bool operator==(const Edge&) noexcept;
		};
	}
}