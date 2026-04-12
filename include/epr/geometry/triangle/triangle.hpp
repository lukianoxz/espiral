#ifndef EPR_GEOMETRY_TRIANGLE_HPP
#define EPR_GEOMETRY_TRIANGLE_HPP

#include <epr/math/vector/vector3.hpp>
#include <epr/geometry/vertex.hpp>
#include <epr/graphics/texture.hpp>

namespace epr::geometry {
    struct Triangle {
        epr::geometry::Vertex vertex[3];

        epr::graphics::Texture internal_texture, external_texture;
    };
}

#endif