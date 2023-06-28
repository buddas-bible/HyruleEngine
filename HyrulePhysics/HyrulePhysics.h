#pragma once
#include "IPhysics.h"

#include <string>
#include <vector>
#include <map>

namespace Hyrule
{
	namespace Physics
	{
		class ICollider;

		class HyrulePhysics : public IPhysics
		{
		public:
			HyrulePhysics() noexcept = default;
			virtual ~HyrulePhysics() = default;

		public:
			virtual ICollider* AddCollider(const std::wstring&) override;
			virtual IRigidBody* AddRigidBody(const std::wstring&) override;

		public:
			virtual long Initialize() override;
			virtual void CollisionCheck() override;
			virtual void RigidSimulation(float) override;
			virtual void WorldReset() override;
			virtual void Finalize() override;
			virtual void SetGravity(float) override;

		private:
			std::map< std::wstring, std::vector< Physics::ICollider* > > colliderMap;
			std::map<std::wstring, IRigidBody*> rigidbodyMap;

			Physics::ICollider* CreateCollider(const std::wstring&);
			IRigidBody* CreateRigidBody(const std::wstring&);
			float gravity;

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