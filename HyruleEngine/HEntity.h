#pragma once
#include <map>
#include <typeinfo>

#include "HObject.h"
#include "ComponentManager.h"

namespace hyrule
{
	class HComponent;
	class HTransform;
	class Scene;

	class HEntity final : public HObject
	{
	public:
		HEntity() = delete;
		HEntity(const std::wstring& _name, Scene* _scene);
		~HEntity() = default;

	private:
		Scene*			scene;								// 내가 포함된 씬..
		HTransform*		transform;							// 트랜스폼
		
		std::string		tag;								// 태그
		bool			activeSelf{ true }; 

		std::map<size_t, HComponent*> components;			// 컴포넌트 리스트

	public:
		Scene* GetScene();
		HTransform* GetTransform();

		const std::string& GetTag();
		void SetTag(const std::string&);

	public:
		void SetActive(bool);
		bool Activated();

		void Awake();
		void OnEnable();

		void Start();
		void FixedUpdate();
		void Update();
		void LateUpdate();

		void OnDisable();
		void OnDestroy();

	public:
		template <typename _cTy>
		std::weak_ptr<_cTy> GetComponent();

		template <typename _cTy>
		std::vector<std::weak_ptr<_cTy>> GetComponents();

		template <typename _cTy>
		std::weak_ptr<_cTy> AddComponent();
	};

	template <typename _cTy>
	std::weak_ptr<_cTy> HEntity::GetComponent()
	{
		std::weak_ptr<ComponentManager> weakPtr = ComponentManager::Instance();

		std::weak_ptr<_cTy> result;

		if (!weakPtr.expired())
		{
			result = weakPtr.lock()->GetComponent<_cTy>(instanceID);
		}

		return result;
	}

	template <typename _cTy>
	std::vector<std::weak_ptr<_cTy>> HEntity::GetComponents()
	{
		std::weak_ptr<ComponentManager> weakPtr = ComponentManager::Instance();

		std::vector<std::weak_ptr<_cTy>> result;

		if (!weakPtr.expired())
		{
			result = weakPtr.lock()->GetComponents<_cTy>(instanceID);
		}

		return result;
	}

	template <typename _cTy>
	std::weak_ptr<_cTy> HEntity::AddComponent()
	{
		std::weak_ptr<ComponentManager> weakPtr = ComponentManager::Instance();

		std::weak_ptr<_cTy> result;

		if (!weakPtr.expired())
		{
			result = weakPtr.lock()->AddComponent<_cTy>(instanceID);
		}

		return result;
	}
}