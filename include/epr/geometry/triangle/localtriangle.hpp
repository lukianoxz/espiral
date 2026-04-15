#ifndef EPR_GEOMETRY_LOCALTRIANGLE_HPP
#define EPR_GEOMETRY_LOCALTRIANGLE_HPP

#include <epr/math/vector/vector3.hpp>
#include <epr/spatial/transform/transform3.hpp>
#include <epr/geometry/vertex.hpp>
#include <epr/graphics/texture.hpp>
#include <epr/geometry/triangle/triangle.hpp>

#include <string>

namespace epr::geometry {
    struct LocalTriangle : public epr::geometry::Triangle {
        LocalTriangle() {}

        LocalTriangle(std::string texture) {
            internal_texture = epr::graphics::Texture::load(texture);
            default_uv();
        }

        epr::spatial::Transform3 origin;
    };
}

#endif