#include "RigidBody.h"

#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

namespace Hyrule
{
	RigidBody::RigidBody(GameObject* _gameObject) noexcept :
		Component(_gameObject), rigidbody()
	{
		
	}

	void RigidBody::LinkRigidBody()
	{
		auto g = gameObject->GetName();
		auto s = gameObject->GetScene()->GetName();

		// ���⼭ �� �̸��� ������Ʈ �̸��� �Ѱ��ְ�
		// �ش� ������Ʈ�� ������ٵ� �޾Ƽ�?
	}
}