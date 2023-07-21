#pragma once
#include "HyruleMath.h"
#include "Edge.h"

namespace Hyrule
{
	struct Vector3D;
	struct Edge;

	namespace Physics
	{
		struct Face
		{
			Face() noexcept = delete;
			Face(const Vector3D&, const Vector3D&, const Vector3D&, 
				size_t, size_t, size_t)noexcept;
			~Face() noexcept;

			void Inverse() noexcept;
			void SetEdge() noexcept;

			Vector3D vec[3];
			size_t index[3];

			Vector3D normal;
			Vector3D center;

			Edge edge[3];
		};
	}
}

