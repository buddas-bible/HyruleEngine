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

			Vector3D position;
			Quaternion rotation;
			Vector3D scale;

			Matrix4x4 worldTM;
			bool isColliding;

		public:
			RigidBody* rigidbody;
			std::vector<Collider*> colliders;

		public:
			Vector3D& GetPosition();
			Quaternion& GetRotation();
			Vector3D& GetScale();

		public:
			Collider* GetCollider(size_t);
			void RemoveCollider(size_t);
			void RemoveCollider(Collider*&);
			RigidBody* GetRigidBody();
			void RemoveRigidBody();
			bool Empty();

		public:
			std::wstring GetName();
			// void SetCollided(bool);
			// bool IsColliding();
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
