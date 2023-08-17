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
	class FirstObserver : public Observable<T>, public IObserver<T>
	{
	public:
		FirstObserver();
		virtual ~FirstObserver() {};
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void()> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
	};

	template <typename T>
	FirstObserver<T>::FirstObserver() {}

	template <typename T>
	void FirstObserver<T>::OnNext(T data)
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnNext(data);
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
		OnComplete();
	}

	template <typename T>
	void FirstObserver<T>::OnComplete()
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
	void FirstObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}