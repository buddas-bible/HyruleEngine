#pragma once
#include <queue>
#include <vector>

namespace Hyrule
{
	class RenderableObject;
	struct Matrix4x4;

	class ObjectManager
	{
		ObjectManager() = default;
		~ObjectManager() = default;
		ObjectManager& operator=(const ObjectManager&) noexcept = delete;
		ObjectManager& operator=(ObjectManager&&) noexcept = delete;

	public:
		static ObjectManager& GetInstance();

	public:
		RenderableObject* CreateObject();
		std::vector<RenderableObject*>& GetRenderableObjects();
		std::vector<RenderableObject*>& GetActivatedObjects();
		void Update(const Matrix4x4&);
		void Render();

		void DisableObject(RenderableObject*);
		void EnableObject(RenderableObject*);

	private:
		std::vector<RenderableObject*> renderableList;		// ���� ��ü ������Ʈ
		std::vector<RenderableObject*> activatedObject;		// Ȱ��ȭ�� ������Ʈ
	};
}

