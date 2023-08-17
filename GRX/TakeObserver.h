#pragma once
#include <functional>
#include <exception>
#include <vector>
#include "IObserver.h"
#include "IObservable.h"
#include "Observable.h"

namespace GRX
{
	template <typename T>
	class TakeObserver : public Observable<T>, public IObserver<T>
	{
	public:
		TakeObserver(int);
		virtual ~TakeObserver() {};
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		int num;
		int count;
	};

	template <typename T>
	TakeObserver<T>::TakeObserver(int num) :
		num(num), count(0) {}

	template <typename T>
	void TakeObserver<T>::OnNext(T data)
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnNext(data);
			}
			count++;
			if (count == num)
			{
				OnComplete();
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void TakeObserver<T>::OnComplete()
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
	void TakeObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}