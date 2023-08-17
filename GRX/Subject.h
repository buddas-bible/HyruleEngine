#pragma once
#include <functional>
#include <exception>
#include <list>
#include "IObserver.h"
#include "IDisposable.h"
#include "Observable.h"
namespace GRX
{
	template <typename T>
	class Subject : public Observable<T>, IObserver<T>
	{
	public:
		Subject();
		~Subject();

	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;
	};

	template<typename T>
	Subject<T>::Subject()
	{

	}

	template<typename T>
	Subject<T>::~Subject()
	{

	}

	template<typename T>
	void Subject<T>::OnNext(T data)
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

	}

	template<typename T>
	void Subject<T>::OnComplete()
	{
		try
		{
			for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
			{
				(*iter)->OnComplete();
			}
		}
		catch (std::exception e)
		{
			OnError(e);
		}
		Observable<T>::Dispose();
	}

	template<typename T>
	void Subject<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}

