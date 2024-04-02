#pragma once
#include <vector>

namespace Hyrule
{
	struct Vector3D;
	struct Matrix4x4;
	struct COLLIDER_INFO;

	struct Quaternion;

	namespace Physics
	{

		class ICollision;


		class ICollider
		{
		public:
			ICollider() = default;
			virtual ~ICollider() = default;

		public:
			virtual bool isCollision() abstract;
			virtual void OnEnable() abstract;
			virtual void OnDisable() abstract;
			virtual void OnDestroy() abstract;

		public:
			/// <summary>
			/// 게임 엔진으로부터 트랜스폼 정보를 받음.
			/// </summary>
			virtual void SetTransform(
				const Vector3D&, const Vector3D&,
				const Vector3D&, const Quaternion&, const Vector3D&) abstract;

			virtual std::vector<ICollision*> GetCollisionInfo() abstract;

			virtual void SetTrigger(bool) abstract;

			// virtual std::wstring GetObjectName() abstract;
			// virtual bool IsColliding() abstract;
		};
	}
}