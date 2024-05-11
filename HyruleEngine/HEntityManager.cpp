#include "HEntity.h"

#include "HEntityManager.h"

namespace hyrule
{
	using namespace std;

	shared_ptr<HEntity> HEntityManager::Create()
	{
		return shared_ptr<HEntity>();
	}

	weak_ptr<HEntity> HEntityManager::Clone(weak_ptr<HEntity> _entity)
	{
		weak_ptr<HEntity> result;

		if (_entity.expired())
		{
			shared_ptr origin = _entity.lock();
			shared_ptr copyEntity = Create();

			origin->GetInstanceID();
		}

		return result;
	}

	void HEntityManager::Destory(weak_ptr<HEntity> _entity)
	{
		if (_entity.expired())
		{
			InstanceID id = _entity.lock()->GetInstanceID();

			if (entities.contains(id))
			{
				entities.erase(id);
			}
		}
	}

	vector<weak_ptr<HEntity>> HEntityManager::Quary(const vector<InstanceID>& _list)
	{
		vector<weak_ptr<HEntity>> result;

		for (auto& _id : _list)
		{
			if (entities.contains(_id))
			{
				result.emplace_back(entities[_id]);
			}
		}

		return result;
	}

	weak_ptr<HEntity> EntityCreate()
	{
		weak_ptr<HEntity> result;

		weak_ptr instance = HEntityManager::Instance();
		if (!instance.expired())
		{
			result = instance.lock()->Create();
		}

		return result;
	}

	weak_ptr<HEntity> EntityClone(weak_ptr<HEntity> _entity)
	{
		weak_ptr<HEntity> result;

		weak_ptr instance = HEntityManager::Instance();
		if (!instance.expired())
		{
			result = instance.lock()->Clone(_entity);
		}

		return result;
	}

	void EntityDestory(weak_ptr<HEntity> _entity)
	{
		weak_ptr instance = HEntityManager::Instance();
		if (!instance.expired())
		{
			instance.lock()->Destory(_entity);
		}
	}

	vector<weak_ptr<HEntity>> EntityQuary(const std::vector<InstanceID>& _list)
	{
		vector<weak_ptr<HEntity>> result;

		weak_ptr instance = HEntityManager::Instance();
		if (!instance.expired())
		{
			result = instance.lock()->Quary(_list);
		}

		return result;
	}
}