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
			bool isColliding;

		public:
			RigidBody* rigidbody;
			std::vector<Collider*> colliders;

		public:
			Collider*& GetCollider(size_t);
			void RemoveCollider(size_t);
			void RemoveCollider(Collider*&);
			bool Empty();

		public:
			void SetCollided(bool);
			bool IsColliding();
			Matrix4x4 SetWorldTM(const Matrix4x4&);
			Matrix4x4 GetWorldTM();
			Matrix3x3 GetInertiaTensor(float);
			Vector3D GetCenterOfMess();

			void CalculateCenterOfMassAndInertiaTensor(float);
		};
	}
}

/*
게임 오브젝트 이름
로컬 트랜스폼
월드 트랜스폼

콜라이더 질량 중심 구하고
콜라이더 부피 구해서 부피 비율로 질량 중심 구하고

*/
