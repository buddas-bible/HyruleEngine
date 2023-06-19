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
		double deltaTime;		// ��Ÿ Ÿ��
		int fps;				// �ʴ� ȣ��� Ƚ��

		__int64 currCount;
		__int64 prevCount;
		__int64 frequency;


		float timeScale;
		bool stopped;			// ������ ����
	};
}