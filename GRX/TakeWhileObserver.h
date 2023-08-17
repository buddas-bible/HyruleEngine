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
	class TakeWhileObserver : public Observable<T>, public IObserver<T>
	{
	public:
		TakeWhileObserver(std::function<bool(T)>);
		virtual ~TakeWhileObserver() {};

	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		std::function<bool(T)> predicate;
	};

	template <typename T>
	TakeWhileObserver<T>::TakeWhileObserver(std::function<bool(T)> predicate) :
		predicate(predicate) {}

	template <typename T>
	void TakeWhileObserver<T>::OnNext(T data)
	{
		try
		{


			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnNext(data);
			}
			if (!predicate(data))
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
	void TakeWhileObserver<T>::OnComplete()
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
	void TakeWhileObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}