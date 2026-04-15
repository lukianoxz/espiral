#ifndef EPR_LOGIC_MOVE_HPP
#define EPR_LOGIC_MOVE_HPP

#include <epr/math/math.hpp>
#include <epr/spatial/spatial.hpp>

namespace epr::logic::motion {
    namespace direction {
        enum Direction {
            FORWARD, BACKWARD, RIGHT, LEFT, UP, DOWN
        };
    }

    static void Move(direction::Direction direction, epr::spatial::Transform3 &origin, float speed, float delta) {
        epr::math::Matrix3 rotation_matrix = origin.rotation.create_yaw_matrix();

        epr::math::Vector3 forward = rotation_matrix * (epr::math::Vector3{0.0f, 0, 1.0f} * speed * delta);
        epr::math::Vector3 right = rotation_matrix * (epr::math::Vector3{1.0f, 0, 0.0f} * speed * delta);

        switch (direction) {
            case direction::FORWARD:
                origin.position -= forward;
                break;
            case direction::BACKWARD:
                origin.position += forward;
                break;
            case direction::RIGHT:
                origin.position += right;
                break;
            case direction::LEFT:
                origin.position -= right;
                break;
            case direction::UP:
                origin.position.y += speed * delta;
                break;
            case direction::DOWN:
                origin.position.y -= speed * delta;
                break;
        }
    }
}

#endif