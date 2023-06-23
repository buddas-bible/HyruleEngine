#pragma once

namespace Hyrule
{
	class Collider;

	class Manifold
	{
	public:
		// Manifold() noexcept = default;
		Manifold(const Collider*& _A, const Collider*& _B) noexcept;
		// ~Manifold() noexcept = default;

	private:
		// �浹 �˻��ϴ� �� �ݶ��̴�
		Collider* A;
		Collider* B;

		// �浹�� �븻 ����
		// �浹�� ź��Ʈ ����
		// �浹�� �̼� ����
		// �浹�� ����
		// �浹 ����				// vector�� �����ϸ� vector�� size�� ���� ���� ���� �� ����
		// ������ �븻 ����
	};
}