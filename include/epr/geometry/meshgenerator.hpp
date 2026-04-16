#ifndef EPR_GEOMETRY_MESHGENERATOR_HPP
#define EPR_GEOMETRY_MESHGENERATOR_HPP

#include <epr/math/math.hpp>
#include <epr/spatial/spatial.hpp>
#include <epr/graphics/texture.hpp>
#include <epr/geometry/triangle/localtriangle.hpp>

#include <vector>
#include <string>
#include <cmath>

namespace epr::geometry::mesh {
    static inline void add_mesh(std::vector <epr::geometry::LocalTriangle> &mesh, std::vector <epr::geometry::LocalTriangle> &other_mesh) {
        mesh.insert(mesh.end(), other_mesh.begin(), other_mesh.end());
    }

    static inline void add_mesh(std::vector <epr::geometry::LocalTriangle> &mesh, std::vector <epr::geometry::LocalTriangle> other_mesh) {
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

    static std::vector <epr::geometry::LocalTriangle> generate_quad(epr::spatial::Transform3 origin, epr::math::Vector2 size, epr::graphics::Texture &texture, epr::graphics::Texture &inverse_texture) {
        std::vector <epr::geometry::LocalTriangle> temp_mesh;

        epr::math::Vector3 triangle_v1_vertex[3] = {
            {size.x, size.y, 0},
            {-size.x, size.y, 0},
            {-size.x, -size.y, 0}
        };

        epr::math::Vector3 triangle_v2_vertex[3] = {
            {-size.x, -size.y, 0},
            {size.x, -size.y, 0},
            {size.x, size.y, 0}
        };

        temp_mesh.push_back(generate_triangle(origin, triangle_v1_vertex, texture));
        temp_mesh.push_back(generate_triangle(origin, triangle_v2_vertex, inverse_texture));

        return temp_mesh;
    }

    static std::vector <epr::geometry::LocalTriangle> generate_plane(epr::spatial::Transform3 origin, epr::math::Vector2 size, epr::math::Vector2i subdivisions, epr::graphics::Texture &texture, epr::graphics::Texture &inverse_texture) {
        std::vector <epr::geometry::LocalTriangle> temp_mesh;

        float quad_size_x = size.x / (float)subdivisions.x;
        float quad_size_y = size.y / (float)subdivisions.y;

        epr::math::Matrix3 rotation = origin.rotation.to_matrix();

        for (int y = 0; y < subdivisions.y; y++) {
            for (int x = 0; x < subdivisions.x; x++) {
                float local_x = ((float)x * quad_size_x + quad_size_x / 2.0f) - size.x / 2.0f;
                float local_y = ((float)y * quad_size_y + quad_size_y / 2.0f) - size.y / 2.0f;

                epr::math::Vector3 loop_position = (epr::math::Vector3){local_x, local_y, 0} * origin.scale;
                loop_position = (rotation * loop_position) + origin.position;

                epr::spatial::Transform3 next_position = {
                    (loop_position),
                    origin.rotation,
                    {1, 1, 1}
                };

                epr::math::Vector2 quad_size = {
                    quad_size_x * 0.5f * origin.scale.x,
                    quad_size_y * 0.5f * origin.scale.y
                };

                add_mesh(temp_mesh, generate_quad(next_position, quad_size, texture, inverse_texture));
            }
        }

        return temp_mesh;
    }
}

#endif