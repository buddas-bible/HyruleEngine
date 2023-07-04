#include "Collider.h"

namespace Hyrule
{
	Collider::Collider(GameObject* _gameObject) noexcept :
		Component(_gameObject),
		collided(), colliderList()
	{

	}

	bool Collider::IsColliding()
	{
		return this->collided;
	}


	void Collider::FixedUpdate()
	{
		// �ݶ��̴� Ʈ������ �Ҹ��� ���� ������Ʈ �ұ�?
	}

	void Collider::Render()
	{
#if _DEBUG
		// ������� �� �ݶ��̴��� �׸����� ��.
#endif
	}
}