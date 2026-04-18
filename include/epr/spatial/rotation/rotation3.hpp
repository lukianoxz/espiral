#ifndef EPR_SPATIAL_ROTATION3_HPP
#define EPR_SPATIAL_ROTATION3_HPP

#include <epr/math/vector/vector3.hpp>
#include <epr/math/matrix/matrix3.hpp>

namespace epr::spatial {
    struct Rotation3 {
        float yaw, pitch, roll;

        epr::math::Matrix3 create_yaw_matrix();
        epr::math::Matrix3 create_pitch_matrix();
        epr::math::Matrix3 create_roll_matrix();

        epr::math::Matrix3 to_matrix();
    };
}

#endif