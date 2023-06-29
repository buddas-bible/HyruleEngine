#pragma once
#include <vector>

namespace Hyrule
{
	struct Vertex;
	struct Vector3D;

	struct Mesh
	{
	public:
		Mesh() = default;
		~Mesh() = default;

	private:
		/// 렌더러블 메쉬 정보가 되는 버텍스와 인덱스 정보
		std::vector<Vertex> vertices;
		std::vector<size_t> index;

		/// 콜라이더 정보가 될 수도 있는 점구름
		std::vector<Vector3D> pointCloud;

		/// fbx 파일을 로드하면 로드 정보를 여기다가 담아두려고 한다.
		/// 이게 맞을까?
		/// 둘이 인덱스 정보를 공유하지도 않을 것이다.
		/// 콜라이더 정보를 위해 인덱스 정보를 하나 더 가지고 있는다?
	};
}