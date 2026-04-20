#ifndef EPR_CORE_SPATIAL_TRANSFORM_TRANSFORM3_HPP
#define EPR_CORE_SPATIAL_TRANSFORM_TRANSFORM3_HPP

#include <epr/core/math/math.hpp>
#include <epr/core/spatial/rotation/rotation3.hpp>

namespace epr::spatial {
    struct Transform3 {
        epr::math::Vector3 position;
        epr::spatial::Rotation3 rotation;
        epr::math::Vector3 scale = {1.0f, 1.0f, 1.0f};

        Transform3() = default;
    };
}

#endif