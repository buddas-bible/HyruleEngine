#pragma once
#include "Component.h"

namespace Hyrule
{
	class GameObject;
	class IRigidBody;

	class RigidBody : public Component
	{
	public:
		RigidBody() = delete;
		RigidBody(GameObject*) noexcept;
		virtual ~RigidBody() = default;

		/// 그저 물리엔진에서의 강체와 이벤트를 연결해주는 무언가.
		/// 강체에 이벤트가... 있던가...?
		IRigidBody* rigidbody;
	};
}


/*
콜라이더를 가진 오브젝트에 충돌 이벤트를 실행시킴.
강체는 정지 했으면 충돌 감지만 할 뿐 추가적인 연산을 하지 않음.
*/