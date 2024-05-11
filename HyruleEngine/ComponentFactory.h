#pragma once
#include <string>
#include <functional>
#include <unordered_map>

namespace hyrule
{
	class Component;

	class ComponentFactory
	{
	public:
		std::unordered_map<size_t, std::function<Component* ()>> componentIDtable;
		std::unordered_map<std::string, std::function<Component* ()>> componentStringtable;
	};

}