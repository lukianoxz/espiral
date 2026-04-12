#ifndef EPR_GEOMETRY_VERTEX_HPP
#define EPR_GEOMETRY_VERTEX_HPP

#include <epr/math/vector/vector2.hpp>
#include <epr/math/vector/vector3.hpp>

namespace epr::geometry {
    struct Vertex {
        epr::math::Vector3 position;
        epr::math::Vector2 uv;
    };
}

#endif