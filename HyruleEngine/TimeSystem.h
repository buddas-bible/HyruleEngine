#pragma once
#include "System.h"
#include "../HyruleUtility/GameTimer.h"

namespace Hyrule
{
	class TimeSystem : public System<TimeSystem>
	{
	public:
		GameTimer gameTimer;

	public:
		void Start();
		void Stop();
		void Reset();
		void Tick();
		float GetfDeltaTime();
		float GetFPS();
	};
}

