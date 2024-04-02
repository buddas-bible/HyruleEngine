#pragma once
#include "Enemy.h"

namespace Hyrule
{
	class MeleeEnemy : public Enemy
	{
	public:
		MeleeEnemy() = delete;
		MeleeEnemy(GameObject*);
		virtual ~MeleeEnemy() = default;
	
	public:
		virtual EnemyState Attack();
		virtual EnemyState Damaged();
		virtual EnemyState Death();
	};
}

