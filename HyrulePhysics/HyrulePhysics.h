#pragma once
#include "IPhysics.h"

#include <string>
#include <vector>
#include <map>

#pragma comment(lib, "HyruleMath.lib")
#include "HyruleMath.h"

namespace Hyrule
{
	struct Vector3D;

	namespace Physics
	{
		class RigidBody;
		class IRigidBody;
		class Collider;
		class ICollider;
		class Object;

		class HyrulePhysics : public IPhysics
		{
		public:
			HyrulePhysics() noexcept = default;
			virtual ~HyrulePhysics() = default;

		public:
			virtual ICollider* AddCollider(const std::wstring&) override;
			virtual IRigidBody* AddRigidBody(const std::wstring&) override;

			virtual void RemoveCollider(const std::wstring&, ICollider*) override;
			virtual void RemoveCollider(const std::wstring&, int) override;
			virtual void RemoveRigidBody(const std::wstring&) override;

		public:
			virtual long Initialize() override;
			virtual void CollisionCheck() override;
			virtual void RigidSimulation(float) override;
			virtual void WorldReset() override;
			virtual void Finalize() override;
			virtual void SetWorldGravity(const Hyrule::Vector3D&) override;

		private:


		private:
			std::map<std::wstring, Object*> objectMap;
			std::vector<Object*> objectList;

			Object* GetObject(const std::wstring&);
			Collider* CreateCollider(Object*);
			RigidBody* CreateRigidBody(Object*);

			Hyrule::Vector3D gravity;

			bool useOctree;
		};

		extern "C"
		{
			__declspec(dllexport) IPhysics* CreatePhysics();
			__declspec(dllexport) void ReleasePhysics(IPhysics*&);
		}
	}
}

/*
게임 엔진으로부터 물리를 분리하고 싶은데

게임 엔진의 강체 컴포넌트, 콜라이더 컴포넌트에 대해서 어떻게 해야하나..
게임 엔진에서 강체 컴포넌트가 추가되면 물리 엔진의 강체를 만들어서 반환 받게 하고...??


또한 디버깅만을 위한 UI를 만들어야 겠다.
물리 관련 디버깅 정보를 그래프로 표시를 한다든가.
충돌 이벤트가 발생한 위치에 무언가로 표시를 해둔다던가...
*/

/*

*/