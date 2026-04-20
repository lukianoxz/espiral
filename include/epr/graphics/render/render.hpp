#ifndef EPR_RENDER_RENDER_HPP
#define EPR_RENDER_RENDER_HPP

#include <epr/core/core.hpp>
#include <epr/graphics/render/scanlines.hpp>
#include <epr/graphics/render/zbuffer.hpp>

#include <vector>
#include <cmath>
#include <memory>

namespace epr::render {
    struct RenderData {
        RenderData(int w, int h) : scanlines(h), z_buffer(w, h) {}

        epr::render::Scanlines scanlines;
        epr::render::ZBuffer z_buffer;
    };

    class Render {
    public:
        void render_mesh(std::vector <epr::geometry::Triangle> &mesh, epr::spatial::Camera &camera, epr::graphics::Viewport &viewport, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines) {
            epr::math::Matrix3 view_matrix = camera.origin.rotation.to_matrix().transpose(); // create inverse rotation matrix
            std::size_t mesh_size = mesh.size();
            epr::geometry::Vertex triangle_vertex[6];
            float fov = std::tan(camera.fov / 2.0f);
            float aspect_x = (float)viewport.w / (float)viewport.h;

            process_view(mesh, view_matrix, camera);
            z_buffer.clear();
            viewport.clear();

            for (std::size_t i = 0; i < mesh_size; i++) {
                epr::geometry::Triangle &triangle = mesh[i];

                process_mesh(triangle, camera, viewport, triangle_vertex, fov, aspect_x, z_buffer, scanlines);
            }

            for (int i = 0; i < viewport.h; i++) {
                for (int j = 0; j < viewport.w; j++) {
                    viewport.draw_pixel(j, i, z_buffer.at(j, i).color);
                }
            }
        }

        void render_mesh(std::vector <epr::geometry::Triangle> &mesh, epr::spatial::Camera &camera, epr::graphics::Viewport &viewport, RenderData &render_data) {
            render_mesh(mesh, camera, viewport, render_data.z_buffer, render_data.scanlines);
        }
    private:
        void process_view(std::vector <epr::geometry::Triangle> &mesh, epr::math::Matrix3 &view_matrix, epr::spatial::Camera &camera);
        void process_mesh(epr::geometry::Triangle &triangle, epr::spatial::Camera &camera, epr::graphics::Viewport &viewport, epr::geometry::Vertex *triangle_vertex, float fov, float aspect_x, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines);
        void process_rasterize(epr::geometry::Vertex *vertex, epr::graphics::Texture &external_texture, float fov, epr::graphics::Viewport &viewport, float aspect_x, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines);
        void process_scanlines(epr::geometry::Vertex *vertex, epr::graphics::Texture &external_texture, epr::graphics::Viewport &viewport, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines);
    };
}

#endif