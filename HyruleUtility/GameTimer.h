#pragma once
#include <chrono>

namespace Hyrule
{
	class GameTimer
	{
	public:
		GameTimer() noexcept;
		~GameTimer() noexcept = default;

		float TotalTime() const;             // in seconds
		float DeltaTime() const;            // in seconds
		float ScalingDeltaTime() const;     // in seconds

		float CurrTime();

		void Reset();                        // Call before message loop.
		void Start();                       // Call when unpaused.
		void Stop();                       // Call when paused.
		void Tick();                       // Call every frame.

	private:
		double timeScale{ 1.0 };
		double mSecondsPerCount;
		double mDeltaTime;


		using second = std::chrono::duration<double>;
		using milli = std::chrono::duration<std::milli>;
		using micro = std::chrono::duration<std::micro>;
		using nano = std::chrono::duration<std::nano>;

		std::chrono::steady_clock::time_point mBaseTime;
		std::chrono::steady_clock::time_point mPausedTime;
		std::chrono::steady_clock::time_point mStopTime;
		std::chrono::steady_clock::time_point mPrevTime;
		std::chrono::steady_clock::time_point mCurrTime;

		bool mStopped;
	};
}