#ifndef EPR_GEOMETRY_TRIANGLE_HPP
#define EPR_GEOMETRY_TRIANGLE_HPP

#include <epr/math/vector/vector3.hpp>
#include <epr/geometry/vertex.hpp>
#include <epr/graphics/texture.hpp>

#include <string>

namespace epr::geometry {
    struct Triangle {
        Triangle() {
            default_uv();
        }

        Triangle(std::string &texture) {
            internal_texture = epr::graphics::Texture::load(texture);
            external_texture = internal_texture;
            default_uv();
        }

        epr::geometry::Vertex vertex[3];
        epr::graphics::Texture internal_texture, external_texture;

        void default_uv() {
            vertex[0].uv = {0, 1};
            vertex[1].uv = {1, 1};
            vertex[2].uv = {1, 0};
        }

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