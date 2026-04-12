#include <epr/render/render.hpp>

void epr::render::Render::process_scanlines(epr::geometry::Vertex *vertex, epr::graphics::Texture &external_texture, epr::graphics::Viewport &viewport, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines) {
    int min_y = vertex[0].position.y, max_y = vertex[0].position.y;

    for (int i = 0; i < 3; i++) {
        int vertex_y = (int)vertex[i].position.y;
        min_y = (vertex_y < min_y) ? vertex_y : min_y;
        max_y = (vertex_y > max_y) ? vertex_y : max_y;
    }

    min_y = min_y < 0 ? 0 : min_y;
    max_y = max_y >= viewport.h ? viewport.h - 1 : max_y;
}