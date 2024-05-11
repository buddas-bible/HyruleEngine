#pragma once
#include <string>
#include "InstanceID.h"

namespace hyrule
{
	class HObject
	{
	protected:
		HObject() = default;
		virtual ~HObject() = default;

	private:
		std::string name_;

	public:
		__declspec(property(put = SetName, get = GetName))
			std::string		name;
		InstanceID			instanceID;

	public:
		InstanceID			GetInstanceID();
		std::string			GetName();
		void				SetName(const std::string&);

	public:
		static void			Destroy(HObject* _object);
		static void			ImmediateDestroy(HObject* _object);
	};
}

