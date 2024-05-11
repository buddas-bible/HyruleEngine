#pragma once
#include "Singleton.h"
#include "../HyruleUtility/GameTimer.h"

namespace hyrule
{
	class TimeSystem : public Singleton<TimeSystem>
	{
	public:
		GameTimer gameTimer;

	public:
		void Start();
		void Stop();
		void Reset();
		void Tick();
		float GetfDeltaTime();
		float FrameStart();
		float GetCurrTime();
		float GetFPS();
	};
}

