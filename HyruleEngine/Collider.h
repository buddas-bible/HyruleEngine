#pragma once
#include "Component.h"

#include <vector>

namespace Hyrule
{
	namespace Physics
	{
		class ICollider;
	}

	class GameObject;

	class Collider : public Component
	{
	public:
		Collider() = delete;
		Collider(GameObject*) noexcept;
		virtual ~Collider() noexcept;

	private:
		// ���� �������� �浹�� �����ϸ�
		// �� ģ���� ���� ������ �����ٵ�...
		// 
		// �װ� ���� �������� �̺�Ʈ �Լ��� ��� ȣ���ϰ� ����?
		// ���� Collider �� üũ�ϰ�
		// Collider �浹 ���θ� ��Ÿ���� bool �� üũ�ϰ�
		// �׷� ������ �ؾ��ϳ�?
		// 
		// �ƴϸ� �浹 ���ζ� ��ü �ùķ��̼Ǹ� ������������ �ϰ�
		// ���� �������� ������ ���� �浹 ���θ� �����س��ٰ�
		// �׿� �´� �浹 �̺�Ʈ �Լ��� ȣ���ϴ°� �³�?
		// 
		// �� �±׿� �ش��ϴ� ģ���鸸 �浹 üũ�ϴ� �׷��� ��� �ؾ��ұ�.
		// ���� ������ Collider�� �±׸� ������ �־�� �ұ�?
		// ����Ƽ������ �±״� ��� �����ϴ� �ɱ�

		std::vector<Physics::ICollider*> colliderList;
		bool collided;

	public:
		bool IsColliding();

	public:
		virtual void Awake() override {}
		virtual void Start() override {}
		virtual void FixedUpdate() override;
		virtual void Update() override {}
		virtual void LastUpdate() override {}
		virtual void Render() override;

		// 		virtual void OnTriggerEnter(Collider*) override {}
		// 		virtual void OnTriggerStay(Collider*) override {}
		// 		virtual void OnTriggerExit(Collider*) override {}
		// 
		// 		virtual void OnTriggerEnter() override;
		// 		virtual void OnTriggerStay() override;
		// 		virtual void OnTriggerExit() override;

		virtual void OnCollisionEnter(Collider*) override {}
		virtual void OnCollisionStay(Collider*) override {}
		virtual void OnCollisionExit(Collider*) override {}

		virtual void OnCollisionEnter() override {}
		virtual void OnCollisionStay() override {}
		virtual void OnCollisionExit() override {}

		virtual void OnEnable() override {}
		virtual void OnDestroy() override {};
	};
}