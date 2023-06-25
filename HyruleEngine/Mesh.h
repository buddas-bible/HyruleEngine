#pragma once
#include <vector>

struct Vertex;

struct Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

private:
	/// 버텍스와 인덱스를 가지고 있겠지?
	std::vector<Vertex> vertex;
	std::vector<size_t> index;

	/// fbx 파일을 로드하면 Mesh* 형태로 반환하도록 해야하지 않을까?
	/// 텍스쳐는 어떻게 해야할까..
	/// 메쉬 렌더러에서 그래픽스에 렌더링을 요청하는 형태니
	/// 아니면 메쉬 렌더러가 리소스를 들고 있다가
	/// 그래픽스의
};

