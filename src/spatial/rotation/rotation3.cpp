#include <epr/spatial/rotation/rotation3.hpp>

#include <cmath>

epr::math::Matrix3 epr::spatial::Rotation3::create_yaw_matrix() {
    epr::math::Matrix3 temp = epr::math::Matrix3::identity();

    temp.data[0][0] = std::cos(rotation.y); temp.data[0][2] = std::sin(rotation.y);
    temp.data[2][0] = -std::sin(rotation.y); temp.data[2][2] = std::cos(rotation.y);

    return temp;
}

epr::math::Matrix3 epr::spatial::Rotation3::create_pitch_matrix() {
    epr::math::Matrix3 temp = epr::math::Matrix3::identity();

    temp.data[1][1] = std::cos(rotation.x); temp.data[1][2] = -std::sin(rotation.x);
    temp.data[2][1] = std::sin(rotation.x); temp.data[2][2] = std::cos(rotation.x);

    return temp;
}

epr::math::Matrix3 epr::spatial::Rotation3::create_roll_matrix() {
    epr::math::Matrix3 temp = epr::math::Matrix3::identity();

    temp.data[0][0] = std::cos(rotation.z); temp.data[0][1] = -std::sin(rotation.z);
    temp.data[1][0] = std::sin(rotation.z); temp.data[1][1] = std::cos(rotation.z);

    return temp;
}

epr::math::Matrix3 epr::spatial::Rotation3::to_matrix() {
    return create_yaw_matrix() * create_pitch_matrix() * create_roll_matrix();
}