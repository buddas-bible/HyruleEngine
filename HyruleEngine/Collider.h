#pragma once
#include "Component.h"

namespace Hyrule
{
	class GameObject;
	class ICollider;

	class Collider : public Component
	{
	public:
		Collider() = delete;
		Collider(GameObject*) noexcept;
		virtual ~Collider() noexcept;

	private:
		// 물리 엔진에서 충돌을 감지하면
		// 이 친구가 뭔가 반응을 해줄텐데...
		// 
		// 그게 게임 엔진에서 이벤트 함수를 어떻게 호출하게 하지?
		// 먼저 Collider 쭉 체크하고
		// Collider 충돌 여부를 나타내는 bool 값 체크하고
		// 그런 식으로 해야하나?
		// 
		// 아니면 충돌 여부랑 강체 시뮬레이션만 물리엔진에서 하고
		// 게임 엔진에서 이전과 지금 충돌 여부를 저장해놨다가
		// 그에 맞는 충돌 이벤트 함수를 호출하는게 맞나?
		// 
		// 또 태그에 해당하는 친구들만 충돌 체크하는 그런건 어떻게 해야할까.
		// 물리 엔진의 Collider도 태그를 가지고 있어야 할까?
		// 유니티에서의 태그는 어디서 관리하는 걸까
		ICollider* collider;
		bool collided;

	public:
		bool IsColliding();
	};
}