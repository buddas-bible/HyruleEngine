#pragma once
#include "Component.h"

namespace Hyrule
{
	class RigidBody : public Component
	{
	public:
		RigidBody() = default;
		virtual ~RigidBody() = default;
	};
}


/*
콜라이더를 가진 오브젝트에 충돌 이벤트를 실행시킴.
강체는 정지 했으면 충돌 감지만 할 뿐 추가적인 연산을 하지 않음.
*/