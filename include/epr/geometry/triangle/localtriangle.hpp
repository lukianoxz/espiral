#ifndef EPR_GEOMETRY_LOCALTRIANGLE_HPP
#define EPR_GEOMETRY_LOCALTRIANGLE_HPP

#include <epr/math/vector/vector3.hpp>
#include <epr/spatial/transform/transform3.hpp>
#include <epr/geometry/vertex.hpp>
#include <epr/graphics/texture.hpp>

namespace epr::geometry {
    struct LocalTriangle {
        epr::spatial::Transform3 origin;
        epr::geometry::Vertex vertex[3];

        epr::graphics::Texture internal_texture, external_texture;
    };
}

#endif