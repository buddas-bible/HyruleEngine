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