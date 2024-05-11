#include "TimeSystem.h"

namespace hyrule
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

	float TimeSystem::FrameStart()
	{
		return 0.f;
	}

	float TimeSystem::GetCurrTime()
	{
		return 0.f;

	}

	float TimeSystem::GetFPS()
	{
		return 1 / gameTimer.DeltaTime();
	}

}