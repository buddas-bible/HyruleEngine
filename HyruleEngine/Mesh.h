#pragma once
#include <vector>

struct Vertex;

struct Mesh
{
public:
	Mesh() = default;
	~Mesh() = default;

private:
	/// ���ؽ��� �ε����� ������ �ְ���?
	std::vector<Vertex> vertex;
	std::vector<size_t> index;

	/// fbx ������ �ε��ϸ� Mesh* ���·� ��ȯ�ϵ��� �ؾ����� ������?
	/// �ؽ��Ĵ� ��� �ؾ��ұ�..
	/// �޽� ���������� �׷��Ƚ��� �������� ��û�ϴ� ���´�
	/// �ƴϸ� �޽� �������� ���ҽ��� ��� �ִٰ�
	/// �׷��Ƚ���
};

