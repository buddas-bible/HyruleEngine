#pragma once
#include "Enemy.h"

namespace Hyrule
{
	class RangeEnemy : public Enemy
	{
	public:
		RangeEnemy() = delete;
		RangeEnemy(GameObject*);
		virtual ~RangeEnemy() = default;

	public:
		void Initialize();
		
		virtual EnemyState Attack();
		virtual EnemyState Damaged();
		virtual EnemyState Death();
	};
}

