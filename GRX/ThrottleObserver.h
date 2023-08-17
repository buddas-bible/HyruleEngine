#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"
#include "IObservable.h"
#include "Observable.h"
#include <Windows.h>

namespace GRX
{
	template <typename T>
	class ThrottleObserver : public Observable<T>, public IObserver<T>
	{
	public:
		ThrottleObserver(float);
		~ThrottleObserver() {}
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;

	private:
		__int64 periodFrequency;
		__int64 curTime;
		__int64 lastTime;
		double timeScale;
		float interval;
		float accumulation;
	};

	template <typename T>
	ThrottleObserver<T>::ThrottleObserver(float interval) :
		interval(interval)
	{
		QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency);

		timeScale = 1.0 / (double)periodFrequency;
		accumulation = FLT_MAX;

	}

	template <typename T>
	void ThrottleObserver<T>::OnNext(T data)
	{
		try
		{
			QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			if (lastTime != 0)
				accumulation += (double)(curTime - lastTime) * timeScale;
			lastTime = curTime;
			if (accumulation > interval)
			{
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(data);
				}
				accumulation = 0;
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void ThrottleObserver<T>::OnComplete()
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnComplete();
			}
			Observable<T>::Dispose();
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void ThrottleObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}