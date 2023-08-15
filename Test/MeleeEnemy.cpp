#include "MeleeEnemy.h"


namespace Hyrule
{
	MeleeEnemy::MeleeEnemy(GameObject* _gameObject) noexcept :
		Enemy(_gameObject)
	{}

	EnemyState MeleeEnemy::Attack()
	{
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