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
(LoadResource<Mesh>('이름', '경로'), (AddResource<Mesh>('이름'))
같은 식으로 템플릿으로 만들어 둘까?


로드 텍스쳐, 로드 메쉬를 하면
해당 클래스를 할당받아서 저장해놓고 있음.

AddComponent<MeshRenderer>같은거 하고?
MeshRenderer에서? 불러올 텍스쳐 이름을 말하면?

아니 이러면 메시렌더러에서 리소스 매니저를 알고 있어야하는걸?

이친구가 메쉬 데이터나 텍스쳐 경로 가지고 있다가?

*/