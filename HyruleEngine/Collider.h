#pragma once
#include "Component.h"

namespace Hyrule
{
	class GameObject;
	class ICollider;

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
		ICollider* collider;
		bool collided;

	public:
		bool IsColliding();
	};
}