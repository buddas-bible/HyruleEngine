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

		void Reset();                        // Call before message loop.
		void Start();                       // Call when unpaused.
		void Stop();                       // Call when paused.
		void Tick();                       // Call every frame.

	private:
		double timeScale{ 1.0 };
		double mSecondsPerCount;
		double mDeltaTime;


		using second = std::chrono::duration<float>;
		using milli = std::chrono::duration<std::milli>;
		using micro = std::chrono::duration<std::micro>;
		using nano = std::chrono::duration<std::nano>;

		std::chrono::high_resolution_clock::time_point mBaseTime;
		std::chrono::high_resolution_clock::time_point mPausedTime;
		std::chrono::high_resolution_clock::time_point mStopTime;
		std::chrono::high_resolution_clock::time_point mPrevTime;
		std::chrono::high_resolution_clock::time_point mCurrTime;

		bool mStopped;
	};
}