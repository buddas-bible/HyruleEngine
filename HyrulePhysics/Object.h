#pragma once
#include <string>
#include <vector>

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

		struct Object
		{
		public:
			Object() noexcept = delete;
			Object(const std::wstring&) noexcept;
			~Object() noexcept = default;

		private:
			std::wstring name;
			Matrix4x4 worldTM;
			
		public:
			RigidBody* rigidbody;
			std::vector<Collider*> colliders;

		public:
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
