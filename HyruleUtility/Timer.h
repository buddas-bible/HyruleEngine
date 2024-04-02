//***************************************************************************************
// GameTimer.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#ifndef GAMETIMER_H
#define GAMETIMER_H

namespace Hyrule
{
	class CTimer
	{
	public:
		CTimer();
		~CTimer() = default;

		float TotalTime() const;  // in seconds
		float DeltaTime() const; // in seconds
		float ScalingDeltaTime() const; // in seconds

		void Reset(); // Call before message loop.
		void Start(); // Call when unpaused.
		void Stop();  // Call when paused.
		void Tick();  // Call every frame.

	private:
		double timeScale{1.f};
		double mSecondsPerCount;
		double mDeltaTime;

		__int64 mBaseTime;
		__int64 mPausedTime;
		__int64 mStopTime;
		__int64 mPrevTime;
		__int64 mCurrTime;

		bool mStopped;
	};
}

#endif // GAMETIMER_H