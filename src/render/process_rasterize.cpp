#include <epr/render/render.hpp>

void epr::render::Render::process_rasterize(epr::geometry::Vertex *vertex, epr::graphics::Texture &external_texture, float fov, epr::graphics::Viewport &viewport, float aspect_x, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines) {
    epr::geometry::Vertex projected_vertex[3];

    float half_w = 0.5 * viewport.w;
    float half_h = 0.5 * viewport.h;

    for (int i = 0; i < 3; i++) {
        vertex[i].position.z = std::abs(vertex[i].position.z) < 0.0001f ? 0.0001 : std::abs(vertex[i].position.z);
        vertex[i].position.x = (1.0f + (vertex[i].position.x * fov) / (vertex[i].position.z * aspect_x)) * half_w;
        vertex[i].position.y = (1.0f - (vertex[i].position.y * fov) / vertex[i].position.z) * half_h;

        projected_vertex[i] = vertex[i];
    }

    int out_top = 0, out_bottom = 0, out_right = 0, out_left = 0;

    for (int i = 0; i < 3; i++) {
        if (projected_vertex[i].position.x < 0) out_left++;
        if (projected_vertex[i].position.x >= viewport.w) out_right++;
        if (projected_vertex[i].position.y < 0) out_top++;
        if (projected_vertex[i].position.y >= viewport.h) out_bottom++;
    }

    if (out_top == 3 || out_bottom == 3 || out_right == 3 || out_left == 3) return;

    process_scanlines(projected_vertex, external_texture, viewport, z_buffer, scanlines);
}