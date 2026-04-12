#include <epr/render/render.hpp>

void epr::render::Render::process_rasterize(epr::geometry::Vertex *vertex, epr::graphics::Texture &external_texture, float fov, epr::graphics::Viewport &viewport, float aspect_x, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines) {
    epr::geometry::Vertex projected_vertex[3];

    for (int i = 0; i < 3; i++) {
        vertex[i].position.z = -vertex[i].position.z;
        vertex[i].position.x = (1.0f + (vertex[i].position.x * fov) / vertex[i].position.z) * 0.5 * aspect_x * viewport.w;
        vertex[i].position.y = (1.0f - (vertex[i].position.y * fov) / vertex[i].position.z) * 0.5 * viewport.h;

        projected_vertex[i] = vertex[i];
    }

    process_scanlines(projected_vertex, external_texture, viewport, z_buffer, scanlines);
}