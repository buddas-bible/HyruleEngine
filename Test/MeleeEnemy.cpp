#include "MeleeEnemy.h"

#include "GameObject.h"
#include "Transform.h"

namespace Hyrule
{
	MeleeEnemy::MeleeEnemy(GameObject* _gameObject) noexcept :
		Enemy(_gameObject)
	{}

	EnemyState MeleeEnemy::Attack()
	{
		gameObject->GetTransform()->GetChild(0);

		// 플레이어를 향해서 공격을 실행시켜야 하는데...
		// 공격 콜라이더 생성 했다가 끄고 그런게 있어야하나

		return EnemyState::DAMAGED;
	}

	EnemyState MeleeEnemy::Damaged()
	{


		return EnemyState::DAMAGED;
	}

	EnemyState MeleeEnemy::Death()
	{
		return EnemyState::DAMAGED;
	}
}