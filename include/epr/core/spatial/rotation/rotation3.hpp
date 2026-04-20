#ifndef EPR_CORE_SPATIAL_ROTATION_ROTATION3_HPP
#define EPR_CORE_SPATIAL_ROTATION_ROTATION3_HPP

#include <epr/core/math/math.hpp>

namespace epr::spatial {
    struct Rotation3 {
        float yaw = 0.0f, pitch = 0.0f, roll = 0.0f;

        epr::math::Matrix3 create_yaw_matrix();
        epr::math::Matrix3 create_pitch_matrix();
        epr::math::Matrix3 create_roll_matrix();

        epr::math::Matrix3 to_matrix();
    };
}

#endif