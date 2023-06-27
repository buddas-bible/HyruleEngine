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

		// 여기서 씬 이름과 오브젝트 이름을 넘겨주고
		// 해당 오브젝트의 리지드바디를 받아서?
	}
}