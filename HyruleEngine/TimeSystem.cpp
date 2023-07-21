#include "TimeSystem.h"

namespace Hyrule
{

	void TimeSystem::Start()
	{
		gameTimer.Start();
	}

	void TimeSystem::Stop()
	{
		gameTimer.Stop();
	}

	void TimeSystem::Reset()
	{
		gameTimer.Reset();
	}

	void TimeSystem::Tick()
	{
		gameTimer.Tick();
	}

	float TimeSystem::GetfDeltaTime()
	{
		return gameTimer.DeltaTime();
	}

	float TimeSystem::GetFPS()
	{
		return 1 / gameTimer.DeltaTime();
	}

}