#pragma once
#include <string>
#include "../HyruleMath/HyruleMath.h"

namespace Hyrule
{
    struct Vector3D;

    namespace Physics
    {
        struct RaycastInfo
        {
            bool collision;
            Vector3D position;
            std::string instaceID;
            std::string tag;
            void* userData;
        };
    }
}