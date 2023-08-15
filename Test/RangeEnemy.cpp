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
		// ��������
		// 
		return EnemyState::DAMAGED;
	}

	EnemyState RangeEnemy::Damaged()
	{
		// ���ݿ� ������ �������� ����
		return EnemyState::DAMAGED;
	}

	EnemyState RangeEnemy::Death()
	{
		// ü���� �� ������ ���
		return EnemyState::DAMAGED;
	}

}