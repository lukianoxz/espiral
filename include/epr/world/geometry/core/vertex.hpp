#ifndef EPR_WORLD_GEOMETRY_CORE_VERTEX_HPP
#define EPR_WORLD_GEOMETRY_CORE_VERTEX_HPP

#include <epr/core/math/math.hpp>

namespace epr::geometry {
    struct Vertex {
        epr::math::Vector3 position;
        epr::math::Vector2 uv;
    };
}

#endif