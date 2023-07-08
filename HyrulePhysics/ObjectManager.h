#pragma once
 #include "Manager.h"

#include <string>
#include <map>
#include <vector>

#include <HyruleMath.h>

namespace Hyrule
{
	struct Matrix4x4;

	namespace Physics
	{
		class Object;
		class ICollider;
		class Collider;
		class IRigidBody;
		class RigidBody;
		struct COLLIDER_INFO;

		class ObjectManager : public Manager<ObjectManager>
		{
		private:
			ObjectManager() noexcept = default;
			~ObjectManager() noexcept = default;
			ObjectManager(const ObjectManager&) = delete;
			void operator=(const ObjectManager&) = delete;

		private:
			std::map<std::wstring, Object*> objectMap;
			std::map<Object*, Matrix4x4> pre;
			std::map<Object*, Matrix4x4> curr;

		public:
			ICollider* AddCollider(const std::wstring&, COLLIDER_INFO*);	// 오브젝트에 콜라이더를 추가함.
			IRigidBody* AddRigidBody(const std::wstring&);					// 오브젝트에 강체를 추가함

			void RemoveCollider(const std::wstring&, ICollider*&);			// 콜라이더 포인터를 받아서 삭제
			void RemoveCollider(const std::wstring&, size_t);				// 콜라이더 인덱스를 받아서 삭제
			void RemoveRigidBody(const std::wstring&);

		private:
			Collider* CreateCollider(Object*, COLLIDER_INFO*);				// 콜라이더를 만듬
			RigidBody* CreateRigidBody(Object*);							// 강체를 만듬

			Object*& GetObject(const std::wstring&);
			Object*& CreateObject(const std::wstring&);
			void RemoveObject(const std::wstring&);
		};
	}
}

