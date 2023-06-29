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
		/// �������� �޽� ������ �Ǵ� ���ؽ��� �ε��� ����
		std::vector<Vertex> vertices;
		std::vector<size_t> index;

		/// �ݶ��̴� ������ �� ���� �ִ� ������
		std::vector<Vector3D> pointCloud;

		/// fbx ������ �ε��ϸ� �ε� ������ ����ٰ� ��Ƶη��� �Ѵ�.
		/// �̰� ������?
		/// ���� �ε��� ������ ���������� ���� ���̴�.
		/// �ݶ��̴� ������ ���� �ε��� ������ �ϳ� �� ������ �ִ´�?
	};
}