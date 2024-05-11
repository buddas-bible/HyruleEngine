#pragma once
#include <Rpc.h>

namespace hyrule
{
	struct InstanceID
	{
		InstanceID() : data1(), data2()
		{
			UuidCreate(&guid);
		}

		union
		{
			_GUID guid;

			struct
			{
				unsigned long ul0;
				unsigned short us0;
				unsigned short us1;
				unsigned char uc[8];
			};

			struct
			{
				long long data1;
				long long data2;
			};
		};

		bool operator<(const InstanceID& _right)
		{
			if (data1 != _right.data1)
				return data1 < _right.data1;
			return data2 < _right.data2;
		}

		bool operator==(const InstanceID& _right)
		{
			if (data1 != _right.data1)
				return false;
			if (data2 != _right.data2)
				return false;
			return true;
		}

		bool operator==(std::nullptr_t)
		{
			return (data1 == 0ll) && (data2 == 0ll);
		}
	};

	struct ComponentID
	{
		size_t typeId;
		InstanceID instanceID;

		bool operator==(const ComponentID& _right)
		{
			if (typeId != _right.typeId)
				return false;
			if (instanceID != _right.instanceID)
				return false;
			return true;
		}
	};

}