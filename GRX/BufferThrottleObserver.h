#pragma once
#include <functional>
#include <exception>
#include <thread>
#include <vector>
#include "IObserver.h"
#include "IObservable.h"
#include "Observable.h"

namespace GRX
{
	template <typename T>
	class BufferThrottleObserver : public Observable<std::vector<T> >, public IObserver<T>
	{
	public:
		BufferThrottleObserver(float time);
		virtual ~BufferThrottleObserver() {};
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;
		void OnNext();


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		int time;
		bool collect;
		std::vector<T> tmp;
	};

	template <typename T>
	BufferThrottleObserver<T>::BufferThrottleObserver(float time) :
		time(time), collect(false) {}

	template <typename T>
	void BufferThrottleObserver<T>::OnNext()
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnNext(tmp);
		}
		tmp.clear();
		collect = false;
	}

	template <typename T>
	void BufferThrottleObserver<T>::OnNext(T data)
	{
		try
		{
			if (!collect)
			{
				std::thread t1([this]()
					{
						std::this_thread::sleep_for(std::chrono::duration<float>(time));
						OnNext();
					});
				t1.detach();
				collect = true;
			}
			if (collect)
			{
				tmp.push_back(data);
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void BufferThrottleObserver<T>::OnComplete()
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnComplete();
			}
			Observable<std::vector<T> >::Dispose();
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void BufferThrottleObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<std::vector<T> >::Dispose();
	}
}