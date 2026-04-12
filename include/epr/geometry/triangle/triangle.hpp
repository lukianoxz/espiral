#ifndef EPR_GEOMETRY_TRIANGLE_HPP
#define EPR_GEOMETRY_TRIANGLE_HPP

#include <epr/math/vector/vector3.hpp>
#include <epr/geometry/vertex.hpp>
#include <epr/graphics/texture.hpp>

namespace epr::geometry {
    struct Triangle {
        epr::geometry::Vertex vertex[3];

        epr::graphics::Texture internal_texture, external_texture;

        epr::math::Vector3 normal() const {
            epr::math::Vector3 v1 = vertex[1].position - vertex[0].position;
            epr::math::Vector3 v2 = vertex[2].position - vertex[0].position;
            return v1.cross(v2);
        }

        epr::math::Vector3 center() const {
            return (vertex[0].position + vertex[1].position + vertex[2].position) / 3.0f;
        }
    };
}

#endif