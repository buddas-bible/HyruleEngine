#pragma once
#include <functional>
#include <exception>
#include <list>
#include "IObservable.h"
#include "IObserver.h"
#include "IDisposable.h"
#include "Observable.h"
namespace GRX
{
	template <typename T>
	class ReactiveProperty : public Observable<T>, public IObserver<T>
	{
	public:
		ReactiveProperty();
		ReactiveProperty(T val);
		~ReactiveProperty();
		T value;
		void operator =(T val)
		{
			value = val;
			OnNext(val);
		}
	public:
		virtual void OnNext(T) override;
		virtual void OnComplete() override;
		virtual void OnError(std::exception) override;
	};

	template<typename T>
	ReactiveProperty<T>::ReactiveProperty()
	{

	}

	template<typename T>
	ReactiveProperty<T>::ReactiveProperty(T val)
	{
		value = val;
	}

	template<typename T>
	ReactiveProperty<T>::~ReactiveProperty()
	{

	}
	template<typename T>
	void ReactiveProperty<T>::OnNext(T data)
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
	void ReactiveProperty<T>::OnComplete()
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
	void ReactiveProperty<T>::OnError(std::exception e)
	{
		for (auto iter = this->observers.begin(); iter != this->observers.end(); iter++)
		{
			(*iter)->OnError(e);
		}
		Observable<T>::Dispose();
	}
}