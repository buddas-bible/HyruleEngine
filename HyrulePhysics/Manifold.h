#pragma once
#include "HRVector.h"


namespace Hyrule
{
	class Collider;

	/// <summary>
	/// �� �ݶ��̴��� �浹 �����������ϴ� Ŭ����
	/// </summary>
	class Manifold
	{
	public:
		// Manifold() noexcept = default;
		Manifold(const Collider*& _A, const Collider*& _B) noexcept;
		// ~Manifold() noexcept = default;

	private:
		// �浹 �˻��ϴ� �� �ݶ��̴�
		Collider const* A;
		Collider const* B;

		// �浹 ����
		Vector3D normal;			// �浹�� �븻 ����
		Vector3D tangent;			// �浹�� ź��Ʈ ����
									// �浹�� �̼� ����
		float depth;				// �浹�� ����
		// std::vector<Vector3D> contactPoints;	// �浹 ����				// vector�� �����ϸ� vector�� size�� ���� ���� ���� �� ����
		Vector3D contactNormal;		// ������ �븻 ����

	public:
		Vector3D GetNormal() const noexcept;
		void SetNormal(const Vector3D& _normal) noexcept;

		Vector3D GetTangent() const noexcept;
		void SetTangent(const Vector3D& _tangent) noexcept;

		Vector3D GetContactNormal() const noexcept;
		void SetContactNormal(const Vector3D& _contactNormal) noexcept;

		float GetDepth() const noexcept;
		void SetDepth(float _depth) noexcept;

		// const std::vector<Vector3D>& GetContactPoints() const;
		// void AddContactPoint(const Vector3& point);

	};
}