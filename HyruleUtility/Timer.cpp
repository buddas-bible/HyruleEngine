#include "framework.h"
#include "Timer.h"

namespace Hyrule
{
	Timer::Timer() noexcept
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&frequency);
	}

	float Timer::fDeltaTime() const noexcept
	{
		return (float)deltaTime;
	}

	double Timer::DeltaTime() const noexcept
	{
		return deltaTime;
	}

	float Timer::ScaledfDeltaTime() const noexcept
	{
		return timeScale * (float)deltaTime;
	}

	double Timer::ScaledDeltaTime() const noexcept
	{
		return (double)timeScale * deltaTime;
	}

	int Timer::GetFramePerSecond() const noexcept
	{
		return fps;
	}

	void Timer::Update() noexcept
	{

	}

	void Timer::Start() noexcept
	{
		
	}

	void Timer::Stop() noexcept
	{

	}

	float Timer::GetTimeScale() const noexcept
	{
		return timeScale;
	}

	void Timer::SetTimeScale(float _scale) noexcept
	{
		timeScale = _scale;
	}
}