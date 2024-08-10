#pragma once
#include <string>
#include "../HyruleMath/HyruleMath.h"

namespace Hyrule
{
    struct Vector3D;

    namespace Physics
    {
        class ICollider;

        class Collision
        {
        public:
            Collision() noexcept = default;

            Collision(const Collision& rhs) noexcept :
                collider(rhs.collider), userData(rhs.userData), instanceID(rhs.instanceID), tag(rhs.tag),
                impulse(rhs.impulse), contactPoints(rhs.contactPoints), normal(rhs.normal) 
            {}
            Collision(Collision&& rhs) noexcept :
                collider(rhs.collider),
                userData(rhs.userData),
                instanceID(rhs.instanceID),
                tag(rhs.tag),
                impulse(rhs.impulse),
                contactPoints(rhs.contactPoints),
                normal(rhs.normal) 
            {}
            ~Collision() noexcept = default;

            Collision& operator= (const Collision& rhs) noexcept
            {
                if (this != &rhs)
                {
                    this->collider = rhs.collider;
                    this->userData = rhs.userData;
                    this->instanceID = rhs.instanceID;
                    this->tag = rhs.tag;
                    this->contactPoints = rhs.contactPoints;
                    this->impulse = rhs.impulse;
                    this->normal = rhs.normal;
                }

                return *this;
            }
            Collision& operator= (Collision&& rhs) noexcept
            {
                if (this != &rhs)
                {
                    this->collider = rhs.collider;
                    this->userData = rhs.userData;
                    this->instanceID = rhs.instanceID;
                    this->tag = rhs.tag;
                    this->contactPoints = rhs.contactPoints;
                    this->impulse = rhs.impulse;
                    this->normal = rhs.normal;
                }

                return *this;
            }

        public:
            ICollider* collider;
            void* userData;
            std::string instanceID;
            std::string tag;
            Vector3D impulse;
            std::vector<Vector3D> contactPoints;
            Vector3D normal;
        };
    }
}