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
������, ���� ���� ������Ʈ���� ��� �� ���ΰ�..
������ ���̺귯���� �����س��´ٸ�
������ ���� ����ü ���� �� ��� �� ���ΰ�..
������ ���̴� ����ü�� �������̽��� ���� ������ AddForce��簡.. ������
���� ���� �Լ��� �����ϴ� ������� �ؾ��ϳ�..




*/