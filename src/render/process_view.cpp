#include <epr/render/render.hpp>

void epr::render::Render::process_view(std::vector <epr::geometry::Triangle> &mesh, epr::math::Matrix3 &view_matrix, epr::spatial::Camera &camera) {
    std::size_t mesh_size = mesh.size();

    for (std::size_t i = 0; i < mesh_size; i++) {
        for (int j = 0; j < 3; j++) {
            epr::math::Vector3 &vertex_position = mesh[i].vertex[j].position;
            vertex_position = view_matrix * (vertex_position - camera.origin.position); // translate vertex around the camera
        }
    }
}