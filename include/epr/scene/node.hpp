#ifndef EPR_SCENE_NODE_HPP
#define EPR_SCENE_NODE_HPP

#include <epr/math/math.hpp>
#include <epr/spatial/spatial.hpp>
#include <epr/graphics/graphics.hpp>
#include <epr/geometry/geometry.hpp>

#include <vector>

namespace epr::scene {
    struct Node {
    public:
        epr::spatial::Transform3 origin;
        std::vector <epr::geometry::LocalTriangle> mesh;

        void add_mesh(std::vector <epr::geometry::LocalTriangle> &mesh_to_add) {
            mesh.insert(mesh.end(), mesh_to_add.begin(), mesh_to_add.end());
        }

        void add_mesh(std::vector <epr::geometry::LocalTriangle> mesh_to_add) {
            mesh.insert(mesh.end(), mesh_to_add.begin(), mesh_to_add.end());
        }

        std::vector <epr::geometry::Triangle> to_world() {
            epr::math::Matrix3 node_matrix = origin.rotation.to_matrix();
            std::vector <epr::geometry::Triangle> world_mesh;

            for (int i = 0; i < mesh.size(); i++) {
                epr::geometry::Triangle temp_triangle;
                temp_triangle.internal_texture = mesh[i].internal_texture;
                temp_triangle.external_texture = mesh[i].internal_texture;
                epr::math::Matrix3 triangle_matrix = mesh[i].origin.rotation.to_matrix();

                // apply uv
                for (int j = 0; j < 3; j++) {
                    temp_triangle.vertex[j].uv = mesh[i].vertex[j].uv;
                }

                // apply scales
                for (int j = 0; j < 3; j++) {
                    temp_triangle.vertex[j].position.x = mesh[i].vertex[j].position.x * mesh[i].origin.scale.x * origin.scale.x;
                    temp_triangle.vertex[j].position.y = mesh[i].vertex[j].position.y * mesh[i].origin.scale.y * origin.scale.y;
                    temp_triangle.vertex[j].position.z = mesh[i].vertex[j].position.z * mesh[i].origin.scale.z * origin.scale.z;
                }

                // apply local triangle rotation
                for (int j = 0; j < 3; j++) {
                    temp_triangle.vertex[j].position = triangle_matrix * temp_triangle.vertex[j].position;
                    temp_triangle.vertex[j].position = temp_triangle.vertex[j].position + mesh[i].origin.position;
                }

                // translate trig around node
                for (int j = 0; j < 3; j++) {
                    temp_triangle.vertex[j].position = node_matrix * temp_triangle.vertex[j].position;
                    temp_triangle.vertex[j].position = temp_triangle.vertex[j].position + origin.position;
                }

                world_mesh.push_back(std::move(temp_triangle));
            }

            return world_mesh;
        }
    private:
        bool mesh_changed;
    };
}

#endif