#pragma once


namespace Hyrule
{
	class Timer
	{
	public:
		Timer() noexcept;
		~Timer() = default;

		float fDeltaTime() const noexcept;
		double DeltaTime() const noexcept;
		float ScaledfDeltaTime() const noexcept;
		double ScaledDeltaTime() const noexcept;

		int GetFramePerSecond() const noexcept;

		void Update() noexcept;
		void Start() noexcept;
		void Stop() noexcept;

		float GetTimeScale() const noexcept;
		void SetTimeScale(float _scale) noexcept;

	private:
		double deltaTime;		// 델타 타임
		int fps;				// 초당 호출된 횟수

		__int64 currCount;
		__int64 prevCount;
		__int64 frequency;


		float timeScale;
		bool stopped;			// 정지된 상태
	};
}