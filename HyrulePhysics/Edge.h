#pragma once
#include "HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		struct Edge
		{
			Edge() = default;
			Edge(const Vector3D&, const Vector3D&, size_t, size_t);
			Edge(const Edge&);
			Edge(Edge&&);
			Edge& operator=(const Edge&);
			Edge& operator=(Edge&&);
			~Edge() = default;

			void Initialze();
			float GetLength() const;
			float GetLengthSquare() const;
			void SetNormal(const Vector3D&);

			Vector3D vectorA;
			Vector3D vectorB;

			size_t index1;
			size_t index2;

			Vector3D direction;
			Vector3D normal;

			bool operator==(const Edge&);
		};
	}
}