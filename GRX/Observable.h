#pragma once
#include "IObservable.h"
#include "IDisposable.h"
#include "Observer.h"
/*
#include "WhereObserver.h"
#include "SelectObserver.h"
#include "DistinctObserver.h"
#include "DistinctUntilChangedObserver.h"
#include "ThrottleObserver.h"
#include "FirstObserver.h"
#include "TakeObserver.h"
#include "TakeUntilObserver.h"
#include "TakeWhileObserver.h"
#include "SkipObserver.h"
#include "SkipUntilObserver.h"
#include "SkipWhileObserver.h"
#include "ScanObserver.h"
#include "BufferCountObserver.h"
#include "BufferThrottleObserver.h"
*/

namespace GRX
{

	template<typename T, typename U>
	class SelectObserver;
	template<typename T>
	class SelectManyObserver;
	template<typename T>
	class DistinctObserver;
	template<typename T>
	class DistinctUntilChangedObserver;
	template<typename T>
	class ThrottleObserver;
	template<typename T>
	class FirstObserver;
	template<typename T>
	class TakeObserver;
	template<typename T>
	class TakeUntilObserver;
	template<typename T>
	class TakeWhileObserver;
	template<typename T>
	class SkipObserver;
	template<typename T>
	class SkipUntilObserver;
	template<typename T>
	class SkipWhileObserver;
	template<typename T>
	class ScanObserver;
	template<typename T>
	class BufferCountObserver;
	template<typename T>
	class BufferThrottleObserver;
	template<typename T>
	class WhereObserver;

	template <typename T>
	class Observable : public IObservable<T>, public IDisposable<T>
	{
	public:
		virtual void Subscribe(std::function<void(T)>);
		virtual void Subscribe(std::function<void(T)>, std::function<void()>) override;
		virtual void Subscribe(std::function<void(T)>, std::function<void()>, std::function<void(std::exception)>) override;
		virtual void Dispose() override;

	public:
		Observable<T>& Where(std::function<bool(T)>);
		template<typename U>
		Observable<U>& Select(std::function<U(T)>);
		Observable<T>& SelectMany(Observable<T>*);
		Observable<T>& Distinct();
		Observable<T>& DistinctUntilChanged();
		Observable<T>& Throttle(float interval);
		Observable<T>& First();
		Observable<T>& Take(int num);
		Observable<T>& TakeUntil(T);
		Observable<T>& TakeWhile(std::function<bool(T)>);
		Observable<T>& Skip(int num);
		Observable<T>& SkipUntil(T);
		Observable<T>& SkipWhile(std::function<bool(T)>);
		Observable<T>& Scan(std::function<T(T, T)>);
		Observable<std::vector<T> >& BufferCount(int bundle, int skip = 0);
		Observable<std::vector<T> >& BufferThrottle(float time);

	public:
		std::vector<IObserver<T>*> observers;

	private:
		static float deltaTime;
	};

	template<typename T>
	void Observable<T>::Subscribe(std::function<void(T)> onNext)
	{
		Observer<T>* newObserver = new Observer<T>(onNext);
		observers.push_back(newObserver);
	}

	template<typename T>
	void Observable<T>::Subscribe(std::function<void(T)> onNext, std::function<void()> onComplete)
	{
		Observer<T>* newObserver = new Observer<T>(onNext, onComplete);
		observers.push_back(newObserver);
	}

	template<typename T>
	void Observable<T>::Subscribe(std::function<void(T)> onNext, std::function<void()> onComplete, std::function<void(std::exception)> onError)
	{
		Observer<T>* newObserver = new Observer<T>(onNext, onComplete, onError);
		observers.push_back(newObserver);
	}

	template<typename T>
	void Observable<T>::Dispose()
	{
		for (auto observer : observers) {
			delete observer;
		}
		observers.clear();
	}

	template<typename T>
	Observable<T>& Observable<T>::Where(std::function<bool(T)> predicate)
	{
		WhereObserver<T>* newObserver = new WhereObserver<T>(predicate);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	template<typename U>
	Observable<U>& Observable<T>::Select(std::function<U(T)> query)
	{
		SelectObserver<T, U>* newObserver = new SelectObserver<T, U>(query);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::SelectMany(Observable<T>* newObserver)
	{
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::Distinct()
	{
		DistinctObserver<T>* newObserver = new DistinctObserver<T>();
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::DistinctUntilChanged()
	{
		DistinctUntilChangedObserver<T>* newObserver = new DistinctUntilChangedObserver<T>();
		observers.push_back(newObserver);
		return *newObserver;
	}


	template<typename T>
	Observable<T>& Observable<T>::Throttle(float interval)
	{
		ThrottleObserver<T>* newObserver = new ThrottleObserver<T>(interval);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::First()
	{
		FirstObserver<T>* newObserver = new FirstObserver<T>();
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::Take(int num)
	{
		TakeObserver<T>* newObserver = new TakeObserver<T>(num);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::TakeUntil(T data)
	{
		TakeUntilObserver<T>* newObserver = new TakeUntilObserver<T>(data);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::TakeWhile(std::function<bool(T)> predicate)
	{
		TakeWhileObserver<T>* newObserver = new TakeWhileObserver<T>(predicate);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::Skip(int num)
	{
		SkipObserver<T>* newObserver = new SkipObserver<T>(num);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::SkipUntil(T data)
	{
		SkipUntilObserver<T>* newObserver = new SkipUntilObserver<T>(data);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::SkipWhile(std::function<bool(T)> predicate)
	{
		SkipWhileObserver<T>* newObserver = new SkipWhileObserver<T>(predicate);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<T>& Observable<T>::Scan(std::function<T(T, T)> func)
	{
		ScanObserver<T>* newObserver = new ScanObserver<T>(func);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<std::vector<T> >& Observable<T>::BufferCount(int bundle, int skip)
	{
		BufferCountObserver<T>* newObserver = new BufferCountObserver<T>(bundle, skip);
		observers.push_back(newObserver);
		return *newObserver;
	}

	template<typename T>
	Observable<std::vector<T> >& Observable<T>::BufferThrottle(float time)
	{
		BufferThrottleObserver<T>* newObserver = new BufferThrottleObserver<T>(time);
		observers.push_back(newObserver);
		return *newObserver;
	}
}