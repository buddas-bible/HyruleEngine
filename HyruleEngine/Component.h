#pragma once

namespace Hyrule
{
	class GameObject;
	class Collider;

	class Component
	{
	public:
		Component() = delete;
		Component(GameObject*) noexcept;
		virtual ~Component() = default;

	protected:
		GameObject* gameObject;

	public:
		virtual void Awake() abstract;
		virtual void Start() abstract;
		virtual void FixedUpdate() abstract;
		virtual void Update() abstract;
		virtual void LastUpdate() abstract;
		virtual void Render() abstract;

		// 		virtual void OnTriggerEnter(Collider*) abstract;
		// 		virtual void OnTriggerStay(Collider*) abstract;
		// 		virtual void OnTriggerExit(Collider*) abstract;
		// 
		// 		virtual void OnTriggerEnter() abstract;
		// 		virtual void OnTriggerStay() abstract;
		// 		virtual void OnTriggerExit() abstract;

		virtual void OnCollisionEnter(Collider*) abstract;
		virtual void OnCollisionStay(Collider*) abstract;
		virtual void OnCollisionExit(Collider*) abstract;

		virtual void OnCollisionEnter() abstract;
		virtual void OnCollisionStay() abstract;
		virtual void OnCollisionExit() abstract;

		virtual void OnEnable() abstract;
		virtual void OnDestroy() abstract;
	};
}


/*
렌더러, 물리 관련 컴포넌트들을 어떻게 할 것인가..
물리를 라이브러리로 구분해놓는다면
물리에 들어가는 구조체 같은 건 어떻게 할 것인가..
물리에 쓰이는 구조체도 인터페이스로 따로 빼놓고 AddForce라든가.. 같은건
관련 수학 함수는 공유하는 방식으로 해야하나..




*/