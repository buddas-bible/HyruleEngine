#include "HObject.h"


namespace hyrule
{
	InstanceID hyrule::HObject::GetInstanceID()
    {
        return instanceID;
    }

	std::string HObject::GetName()
	{
		return name_;
	}

	void HObject::SetName(const std::string& _str)
	{
		name_ = std::move(_str);
	}

	void HObject::Destroy(HObject* _object)
	{
		// Destroy Queue에 넣고 일괄 처리
	}

	void HObject::ImmediateDestroy(HObject* _object)
	{
		
	}
}
