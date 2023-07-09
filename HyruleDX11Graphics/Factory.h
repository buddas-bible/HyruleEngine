#pragma once
#include "Interface_.h"

template <typename T>
class Interface_;


class IBuilder
{
public:
	virtual void* Build() abstract;
};

template <typename T>
class Builder
{
public:
	virtual T* Build() override;
};

class ResourceBuilder : Builder<ResourceBuilder>
{

};

class Factory
{
public:

	template <typename T, typename U>
	T* Build(const Interface_<T>*& _interface)
	{
		T* instance = new T;
	}
};

