#include "GameTimer.h"

namespace Hyrule
{
	GameTimer::GameTimer() noexcept
		: mSecondsPerCount(0.0), mDeltaTime(-1.0), mStopped(false)
	{
		auto countsPerSec = std::chrono::high_resolution_clock::period::den;
		mSecondsPerCount = 1.0 / static_cast<double>(countsPerSec);
	}

	float GameTimer::TotalTime() const
	{
		std::chrono::duration<double> totalTime;
		if (mStopped)
		{
			totalTime = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
				(mStopTime - mPausedTime) - mBaseTime.time_since_epoch());
		}
		else
		{
			totalTime = std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
				(mCurrTime - mPausedTime) - mBaseTime.time_since_epoch());
		}

		return static_cast<float>(totalTime.count()) * mSecondsPerCount;
	}

	float GameTimer::DeltaTime() const
	{
		return static_cast<float>(mDeltaTime);
	}

	float GameTimer::ScalingDeltaTime() const
	{
		return static_cast<float>(mDeltaTime * timeScale);
	}

	void GameTimer::Reset()
	{
		mBaseTime = std::chrono::high_resolution_clock::now();
		mPrevTime = mBaseTime;
		mStopTime = std::chrono::high_resolution_clock::time_point();
		mStopped = false;
	}

	void GameTimer::Start()
	{
		auto startTime = std::chrono::high_resolution_clock::now();

		if (mStopped)
		{
			auto pausedDuration = 
				std::chrono::duration_cast<std::chrono::high_resolution_clock::duration>(
				startTime - mStopTime
				);
			mPausedTime += pausedDuration;

			mPrevTime = startTime;
			mStopTime = std::chrono::high_resolution_clock::time_point();
			mStopped = false;
		}
	}

	void GameTimer::Stop()
	{
		if (!mStopped)
		{
			mStopTime = std::chrono::high_resolution_clock::now();
			mStopped = true;
		}
	}

	void GameTimer::Tick()
	{
		if (mStopped)
		{
			mDeltaTime = 0.0;
			return;
		}

		mCurrTime = std::chrono::high_resolution_clock::now();

		std::chrono::duration<double> deltaTime = mCurrTime - mPrevTime;
		mDeltaTime = deltaTime.count();

		mPrevTime = mCurrTime;

		if (mDeltaTime < 0.0)
		{
			mDeltaTime = 0.0;
		}
	}
}