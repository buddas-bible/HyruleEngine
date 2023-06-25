#pragma once


namespace Hyrule
{
	class ResourceManager
	{
	public:
		ResourceManager();
		~ResourceManager();

	public:
		void LoadTexture(/*const std::wstring& _name*//*const std::wstring& _path*/) noexcept;
		void LoadMesh(/*const std::wstring& _name*//*const std::wstring& _path*/);

		// std::map<std::wstring, Mesh*>
		// std::map<std::wstring, Texture*>
	};
}


/*
(LoadResource<Mesh>('�̸�', '���'), (AddResource<Mesh>('�̸�'))
���� ������ ���ø����� ����� �ѱ�?


�ε� �ؽ���, �ε� �޽��� �ϸ�
�ش� Ŭ������ �Ҵ�޾Ƽ� �����س��� ����.

AddComponent<MeshRenderer>������ �ϰ�?
MeshRenderer����? �ҷ��� �ؽ��� �̸��� ���ϸ�?

�ƴ� �̷��� �޽÷��������� ���ҽ� �Ŵ����� �˰� �־���ϴ°�?

��ģ���� �޽� �����ͳ� �ؽ��� ��� ������ �ִٰ�?

*/