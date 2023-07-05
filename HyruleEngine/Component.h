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
������, ���� ���� ������Ʈ���� ��� �� ���ΰ�..
������ ���̺귯���� �����س��´ٸ�
������ ���� ����ü ���� �� ��� �� ���ΰ�..
������ ���̴� ����ü�� �������̽��� ���� ������ AddForce��簡.. ������
���� ���� �Լ��� �����ϴ� ������� �ؾ��ϳ�..




*/