#include "Collider.h"

namespace Hyrule
{
	Collider::Collider(GameObject* _gameObject) noexcept :
		Component(_gameObject),
		collided(), colliderList()
	{

	}

	bool Collider::IsColliding()
	{
		return this->collided;
	}


	void Collider::FixedUpdate()
	{
		// 콜라이더 트랜스폼 불리언 값을 업데이트 할까?
	}

	void Collider::Render()
	{
#if _DEBUG
		// 디버그일 때 콜라이더를 그리도록 함.
#endif
	}
}