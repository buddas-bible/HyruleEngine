#pragma once
#include "IPhysicsWorld.h"

#include <string>
#include <map>

namespace Hyrule
{
	class HyrulePhysics : public IPhysicsWorld
	{
	public:
		HyrulePhysics() noexcept = delete;
		HyrulePhysics(float) noexcept;
		virtual ~HyrulePhysics() = default;

	public:
		virtual ICollider* AddCollider() override;
		virtual IRigidBody* AddRigidBody() override;

	public:
		virtual int Initialize() override;
		virtual void CollisionCheck() override;
		virtual void RigidSimulation(float) override;
		virtual void WorldReset() override;
		virtual void Finalize() override;
		virtual void SetGravity(float) override;

	private:
		std::map<std::wstring, std::vector<ICollider*>> colliderMap;
		std::map<std::wstring, IRigidBody*> rigidbodyMap;

		ICollider* CreateCollider(const std::wstring&);
		IRigidBody* CreateRigidBody(const std::wstring&);
		float gravity;

	};
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