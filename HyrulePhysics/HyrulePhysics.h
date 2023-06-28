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
���� �������κ��� ������ �и��ϰ� ������

���� ������ ��ü ������Ʈ, �ݶ��̴� ������Ʈ�� ���ؼ� ��� �ؾ��ϳ�..
���� �������� ��ü ������Ʈ�� �߰��Ǹ� ���� ������ ��ü�� ���� ��ȯ �ް� �ϰ�...??


���� ����븸�� ���� UI�� ������ �ڴ�.
���� ���� ����� ������ �׷����� ǥ�ø� �Ѵٵ簡.
�浹 �̺�Ʈ�� �߻��� ��ġ�� ���𰡷� ǥ�ø� �صдٴ���...
*/

/*

*/