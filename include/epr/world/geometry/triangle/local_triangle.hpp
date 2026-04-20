#ifndef EPR_WORLD_GEOMETRY_TRIANGLE_LOCAL_TRIANGLE_HPP
#define EPR_WORLD_GEOMETRY_TRIANGLE_LOCAL_TRIANGLE_HPP

#include <epr/core/math/math.hpp>
#include <epr/core/spatial/spatial.hpp>
#include <epr/world/geometry/triangle/triangle.hpp>

#include <string>

namespace epr::geometry {
    struct LocalTriangle : public epr::geometry::Triangle {
        LocalTriangle() {}

        LocalTriangle(epr::graphics::Texture &texture) {
            internal_texture = texture;
            default_uv();
        }

        epr::spatial::Transform3 origin;
    };
}

#endif