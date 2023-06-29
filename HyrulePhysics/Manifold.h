#pragma once
#include <vector>

#pragma comment(lib, "HyruleMath.lib")
#include "../HyruleMath/HyruleMath.h"

namespace Hyrule
{
	namespace Physics
	{
		class Collider;

		/// <summary>
		/// �� �ݶ��̴��� �浹 �����������ϴ� Ŭ����
		/// </summary>
		class Manifold
		{
		public:
			// Manifold() noexcept = default;
			Manifold(Collider*& _A, Collider*& _B) noexcept;
			~Manifold() noexcept = default;

		private:
			// �浹 �˻��ϴ� �� �ݶ��̴�
			Collider* A;
			Collider* B;

			// �浹 ����
			Hyrule::Vector3D normal;						// �浹�� �븻 ����
			Hyrule::Vector3D tangent;						// �浹�� ź��Ʈ ����
															// �浹�� �̼� ����
			float depth;									// �浹�� ����
			std::vector<Hyrule::Vector3D> contactPoints;	// �浹 ����				// vector�� �����ϸ� vector�� size�� ���� ���� ���� �� ����
			Hyrule::Vector3D contactNormal;					// ������ �븻 ����

			float friction;

			bool collided;

		public:
			bool IsColliding();

			Vector3D GetNormal() const noexcept;
			void SetNormal(const Vector3D& _normal) noexcept;

			Vector3D GetTangent() const noexcept;
			void SetTangent(const Vector3D& _tangent) noexcept;

			Vector3D GetContactNormal() const noexcept;
			void SetContactNormal(const Vector3D& _contactNormal) noexcept;

			float GetDepth() const noexcept;
			void SetDepth(float _depth) noexcept;

			const std::vector<Vector3D>& GetContactPoints() const;
			void AddContactPoint(const Vector3D& point);

		private:
			/// <summary>
			/// �Ŵ����尡 GJK�� ������ �ִ� ���� �ƴ�
			/// GJK�� ��ȯ�� �Ŵ����尡 �Ǿ���� �� ����.
			/// �浹�ϸ� �Ŵ����带 ��ȯ
			/// �浹���� ������ nullptr�� ��ȯ�ϴ� ������� �ؼ�
			/// 
			/// �ƴϸ� �׳� GJK�� EPA�� �Լ� ��ü�� ������
			/// </summary>
			void CheckCollision();

			void CollisionEvent();

		};
	}
}