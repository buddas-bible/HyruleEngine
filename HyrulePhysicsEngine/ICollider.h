#pragma once
#include <vector>
#include "../HyrulePhysicsEngine/Collision.h"

namespace Hyrule
{
    struct Vector3D;
    struct Matrix4x4;
    struct COLLIDER_INFO;

    struct Quaternion;
    struct Collision;

    namespace Physics
    {

        class ICollision;


        class ICollider
        {
        public:
            ICollider() noexcept = default;
            virtual ~ICollider() noexcept = default;

        public:
            virtual bool isCollision() noexcept abstract;
            virtual void OnEnable() noexcept abstract;
            virtual void OnDisable() noexcept abstract;
            virtual void OnDestroy() noexcept abstract;

        public:
            /// <summary>
            /// 게임 엔진으로부터 트랜스폼 정보를 받음.
            /// </summary>
            virtual void SetTransform(
                const Vector3D&, const Vector3D&,
                const Vector3D&, const Quaternion&, const Vector3D&) noexcept abstract;

            virtual std::vector<Hyrule::Physics::Collision>& GetCollisionInfo() noexcept abstract;

            virtual void SetTrigger(bool) abstract;
            virtual void SetSize(const Vector3D&) abstract;
            virtual void SetCenter(const Vector3D&) abstract;

            // virtual std::wstring GetObjectName() abstract;
            // virtual bool IsColliding() abstract;
        };
    }
}