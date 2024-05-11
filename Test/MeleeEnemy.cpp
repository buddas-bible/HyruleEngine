#include "MeleeEnemy.h"

#include "HEntity.h"
#include "HTransform.h"

namespace hyrule
{
	MeleeEnemy::MeleeEnemy(GameObject* _gameObject) :
		Enemy(_gameObject)
	{}

	EnemyState MeleeEnemy::Attack()
	{
		gameObject->GetTransform()->GetChild(0);

		// �÷��̾ ���ؼ� ������ ������Ѿ� �ϴµ�...
		// ���� �ݶ��̴� ���� �ߴٰ� ���� �׷��� �־���ϳ�

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