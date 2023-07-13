#pragma once
#include <string>
#include <vector>
#include <memory>
#include "HyruleMath.h"

namespace Hyrule
{
	struct Matrix4x4;
	struct Matrix3x3;
	struct Vector3D;
	struct Quaternion;

	namespace Physics
	{
		// struct TRANSFORM_INFO;
		// class Transform;
		class RigidBody;
		class Collider;

		class Object
		{
		public:
			Object() noexcept = delete;
			Object(const std::wstring&) noexcept;
			~Object() noexcept = default;

		private:
			std::wstring name;
			Matrix4x4 worldTM;
			bool isColliding;

		public:
			std::shared_ptr<RigidBody> rigidbody;
			std::vector<std::shared_ptr<Collider>> colliders;

		public:
			Collider* GetCollider(size_t);
			void RemoveCollider(size_t);
			void RemoveCollider(Collider*&);
			bool Empty();

		public:
			void SetCollided(bool);
			bool IsColliding();
			void SetWorldTM(const Matrix4x4&);
			Matrix4x4 GetWorldTM();
			Matrix3x3 GetInertiaTensor(float);
			Vector3D GetCenterOfMess();

			void CalculateCenterOfMassAndInertiaTensor(float);
		};
	}
}

/*
���� ������Ʈ �̸�
���� Ʈ������
���� Ʈ������

�ݶ��̴� ���� �߽� ���ϰ�
�ݶ��̴� ���� ���ؼ� ���� ������ ���� �߽� ���ϰ�

*/
