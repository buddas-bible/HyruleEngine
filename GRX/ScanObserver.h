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
	class ScanObserver : public Observable<T>, public IObserver<T>
	{
	public:
		ScanObserver(std::function<T(T, T)>);
		virtual ~ScanObserver() {};

	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;


	public:
		std::function<void(T)> onNextCallback;
		std::function<void(T)> onCompleteCallback;
		std::function<void(std::exception)> onErrorCallback;
		bool first;
		T accumulation;
		std::function<T(T, T)> func;
	};

	template <typename T>
	ScanObserver<T>::ScanObserver(std::function<T(T, T)> func) :
		func(func), first(true) {}

	template <typename T>
	void ScanObserver<T>::OnNext(T data)
	{
		try
		{
			if (first)
			{
				accumulation = data;
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(accumulation);
				}
				first = false;
			}
			else
			{
				accumulation = func(accumulation, data);
				for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
				{
					(*iter)->OnNext(accumulation);
				}

			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
	}

	template <typename T>
	void ScanObserver<T>::OnComplete()
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
	void ScanObserver<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}