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
	class SkipUntilObserver : public Observable<T>, public IObserver<T>
	{
	public:
		SkipUntilObserver(T);
		virtual ~SkipUntilObserver() {};

	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		T value;
		bool skip;
	};

	template <typename T>
	SkipUntilObserver<T>::SkipUntilObserver(T value) :
		value(value), skip(true) {}

	template <typename T>
	void SkipUntilObserver<T>::OnNext(T data)
	{
		try
		{
			if (skip && value == data)
			{
				skip = false;
			}
			if (!skip)
			{
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(data);
				}
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void SkipUntilObserver<T>::OnComplete()
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
	void SkipUntilObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}