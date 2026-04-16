#ifndef EPR_GEOMETRY_MESHGENERATOR_HPP
#define EPR_GEOMETRY_MESHGENERATOR_HPP

#include <epr/math/math.hpp>
#include <epr/spatial/spatial.hpp>
#include <epr/graphics/texture.hpp>
#include <epr/geometry/triangle/localtriangle.hpp>

#include <vector>
#include <string>

namespace epr::geometry::mesh {
    static inline void add_mesh(std::vector <epr::geometry::LocalTriangle> &mesh, std::vector <epr::geometry::LocalTriangle> &other_mesh) {
        mesh.insert(mesh.end(), other_mesh.begin(), other_mesh.end());
    }

    static epr::geometry::LocalTriangle generate_triangle(epr::spatial::Transform3 origin ,epr::math::Vector3 vertex_position[], epr::graphics::Texture &texture) {
        epr::geometry::LocalTriangle temp;

        temp.internal_texture = texture;
        temp.external_texture = texture;

        temp.origin = origin;

        temp.vertex[0].position = vertex_position[0];
        temp.vertex[1].position = vertex_position[1];
        temp.vertex[2].position = vertex_position[2];

        return temp;
    }

    static std::vector <epr::geometry::LocalTriangle> generate_quad(epr::spatial::Transform3 origin, epr::graphics::Texture &texture, epr::graphics::Texture &inverse_texture) {
        std::vector <epr::geometry::LocalTriangle> temp_mesh;

        epr::math::Vector3 triangle_v1_vertex[3] = {
            {1, 1, 0},
            {-1, 1, 0},
            {-1, -1, 0}
        };

        epr::math::Vector3 triangle_v2_vertex[3] = {
            {-1, -1, 0},
            {1, -1, 0},
            {1, 1, 0}
        };

        temp_mesh.push_back(generate_triangle(origin, triangle_v1_vertex, texture));
        temp_mesh.push_back(generate_triangle(origin, triangle_v2_vertex, inverse_texture));

        return temp_mesh;
    }
}

#endif