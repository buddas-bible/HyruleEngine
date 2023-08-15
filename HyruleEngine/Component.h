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
		virtual ~Component() noexcept = default;

	public:
		GameObject* gameObject;

	public:
		virtual void Awake() {};
		virtual void Start() {};
		virtual void FixedUpdate() {};
		virtual void PrePhysicsUpdate() {};
		virtual void PhysicsUpdate() {};
		virtual void LatePhysicsUpdate() {};
		virtual void Update() {};
		virtual void LateUpdate() {};
		virtual void Render() {};

		// 		virtual void OnTriggerEnter(Collider*)  {};
		// 		virtual void OnTriggerStay(Collider*)  {};
		// 		virtual void OnTriggerExit(Collider*)  {};
		// 
		// 		virtual void OnTriggerEnter()  {};
		// 		virtual void OnTriggerStay()  {};
		// 		virtual void OnTriggerExit()  {};

		virtual void OnCollisionEnter(Collider*) {};
		virtual void OnCollisionStay(Collider*) {};
		virtual void OnCollisionExit(Collider*) {};

		virtual void OnCollisionEnter() {};
		virtual void OnCollisionStay() {};
		virtual void OnCollisionExit() {};

		virtual void OnEnable() {};
		virtual void OnDisable() {};
		virtual void OnDestroy() {};
	};
}


/*
렌더러, 물리 관련 컴포넌트들을 어떻게 할 것인가..
물리를 라이브러리로 구분해놓는다면
물리에 들어가는 구조체 같은 건 어떻게 할 것인가..
물리에 쓰이는 구조체도 인터페이스로 따로 빼놓고 AddForce라든가.. 같은건
관련 수학 함수는 공유하는 방식으로 해야하나..




*/