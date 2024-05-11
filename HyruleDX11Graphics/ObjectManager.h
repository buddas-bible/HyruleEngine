#pragma once
#include <queue>
#include <vector>

namespace hyrule
{
	class RenderableObject;
	struct Matrix4x4;
	struct Vector3D;

	class ObjectManager
	{
		ObjectManager() = default;
		~ObjectManager() = default;
		ObjectManager& operator=(const ObjectManager&) = delete;
		ObjectManager& operator=(ObjectManager&&) = delete;

	public:
		static ObjectManager& GetInstance();

	public:
		RenderableObject* CreateObject();
		std::vector<RenderableObject*>& GetRenderableObjects();
		// std::vector<RenderableObject*>& GetActivatedObjects();
		void AddObject(RenderableObject*);
		void Update(const Matrix4x4&);
		void Render(const Vector3D& eye);

		// void DisableObject(RenderableObject*);
		// void EnableObject(RenderableObject*);

	private:
		std::vector<RenderableObject*> renderableList;		// ���� ��ü ������Ʈ
		// std::vector<RenderableObject*> activatedObject;		// Ȱ��ȭ�� ������Ʈ
	};
}

