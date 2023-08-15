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

		// �÷��̾ ���ؼ� ������ ������Ѿ� �ϴµ�...

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