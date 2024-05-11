#pragma once
#include <memory>
#include <unordered_map>
#include "InstanceID.h"
#include "Singleton.h"

namespace hyrule
{
	class HEntity;

	class HEntityManager : public Singleton<HEntityManager>
	{
	public:
		std::shared_ptr<HEntity>	Create();
		std::weak_ptr<HEntity>		Clone(std::weak_ptr<HEntity> _entity);
		void						Destory(std::weak_ptr<HEntity> _entity);

	public:
		std::vector<std::weak_ptr<HEntity>> Quary(const std::vector<InstanceID>&);

	private:
		std::unordered_map<InstanceID, std::shared_ptr<HEntity>> entities;
		std::unordered_map<InstanceID, std::shared_ptr<HEntity>> dontDestroyEntities;
	};

	std::weak_ptr<HEntity>			EntityCreate();
	std::weak_ptr<HEntity>			EntityClone(std::weak_ptr<HEntity> _entity);
	void							EntityDestory(std::weak_ptr<HEntity> _entity);
	std::vector<std::weak_ptr<HEntity>> EntityQuary(const std::vector<InstanceID>&);
}

