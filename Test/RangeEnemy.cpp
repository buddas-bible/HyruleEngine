#include "RangeEnemy.h"

#include "GameObject.h"
#include "Transform.h"

namespace Hyrule
{
#define DELTATIME_ 0.016f

	RangeEnemy::RangeEnemy(GameObject* _gameObject) noexcept :
		Enemy(_gameObject)
	{
		HP			= 15;
		speed		= 1;
		attackRange = 5;
		detactRange = 7;
		// attackType
		chargeTime	= 0.5f;
		castTime	= 2.f;
		damage		= 1;
	}

	void RangeEnemy::Initialize()
	{
		HP = 15;
		speed = 1;
		attackRange = 5;
		detactRange = 7;
		// attackType
		chargeTime = 0.5f;
		castTime = 2.f;
		damage = 1;
	}

	EnemyState RangeEnemy::Attack()
	{
		// 전투상태
		// 
		return EnemyState::DAMAGED;
	}

	EnemyState RangeEnemy::Damaged()
	{
		// 공격에 맞으면 데미지를 받음
		return EnemyState::DAMAGED;
	}

	EnemyState RangeEnemy::Death()
	{
		// 체력이 다 닳으면 사망
		return EnemyState::DAMAGED;
	}

}