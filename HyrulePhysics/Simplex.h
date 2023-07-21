#pragma once

#include <vector>
#include <set>
#include <map>
#include "HyruleMath.h"


namespace Hyrule
{
	namespace Physics
	{
		struct Face;

		class Simplex
		{
		public:
			Simplex() noexcept = default;
			~Simplex() noexcept;

			Vector3D& operator[](int);
			std::vector<Vector3D>& operator=(const std::vector<Vector3D>&);
			std::vector<Vector3D>& operator=(std::vector<Vector3D>&&);
			
			void push_back(const Vector3D&);
			size_t size();

			// void SetIndices();
			void SetFace();
			void AddFace(size_t, size_t, size_t);
			// std::map<float, Face*> faceMap;
			std::map<float, Face> faceMap;

			std::vector<Vector3D> points;
			std::set<std::vector<size_t>> index;
		};
	}
}

