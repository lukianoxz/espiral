#ifndef EPR_SPATIAL_TRANSFORM3_HPP
#define EPR_SPATIAL_TRANSFORM3_HPP

#include <epr/math/vector/vector3.hpp>
#include <epr/spatial/rotation/rotation3.hpp>

namespace epr::spatial {
    struct Transform3 {
        epr::math::Vector3 position;
        epr::spatial::Rotation3 rotation;
        epr::math::Vector3 scale = {1.0f, 1.0f, 1.0f};
    };
}

#endif