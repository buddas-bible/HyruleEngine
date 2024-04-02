#pragma once
#include "MonoBehaviour.h"

#include <map>
#include <vector>

#define COMPONENT_REGISTRY( Type, name ) \
Type() = delete; \
Type(GameObject* _gameObject) : MonoBehaviour(_gameObject)\
{ name = #Type; }\

namespace Hyrule
{
	class GameObject;

	class Controller : public MonoBehaviour
	{
	public:
		COMPONENT_REGISTRY(Controller);

	private:
		std::map<int, std::vector<GameObject*>> controlMap;
		std::vector<GameObject*> controlObject;

	public:
		void AddControllableObject(int, GameObject*);

	public:
		virtual void Awake() override;
		virtual void Start() override;
		virtual void FixedUpdate() override;
		virtual void Update() override;
		virtual void LateUpdate() override;

		virtual void OnEnable() override;
		virtual void OnDisable() override;
		virtual void OnDestroy() override;
	};
}

