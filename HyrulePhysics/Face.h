#pragma once
#include "HyruleMath.h"
#include "Edge.h"
#include <vector>

namespace hyrule
{
	struct Vector3D;
	struct Edge;

	namespace Physics
	{
		struct Face
		{
			Face() = delete;
			Face(const Vector3D&, const Vector3D&, const Vector3D&, 
				size_t, size_t, size_t)noexcept;
			Face(const std::vector<Edge>&);
			~Face();

			void Inverse();
			void SetEdge();

			std::vector<Vector3D> vec;
			std::vector<size_t> index;
			std::vector<Edge> edge;


			Vector3D normal;
			Vector3D center;
		};
	}
}

