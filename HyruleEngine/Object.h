#pragma once
#include <string>

namespace Hyrule
{
	class Object
	{
	protected:
		Object() = default;
		virtual ~Object() = default;

	private:
		std::string name_;

	public:
		__declspec(property(put = SetName, get = GetName))
			std::string		name;
		int				instanceID;

	public:
		int				GetInstanceID();
		std::string		GetName();
		void			SetName(const std::string&);

	public:
		static void		Destroy(Object* _object);
	};
}

