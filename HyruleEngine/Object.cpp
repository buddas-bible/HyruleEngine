#include "Object.h"


namespace Hyrule
{
    int Hyrule::Object::GetInstanceID()
    {
        return instanceID;
    }

	std::string Object::GetName()
	{
		return name_;
	}

	void Object::SetName(const std::string& _str)
	{
		name_ = std::move(_str);
	}

	void Object::Destroy(Object* _object)
	{
		// Destroy Queue俊 持绊 老褒 贸府
	}
}
