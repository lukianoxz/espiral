#include <epr/graphics/render/render.hpp>

#include <vector>

epr::geometry::Vertex intersect(epr::geometry::Vertex &a, epr::geometry::Vertex &b, float near) {
    float t = (near - a.position.z) / (b.position.z - a.position.z);
    return {
        a.position + (b.position - a.position) * t,
        {a.uv.x + (b.uv.x - a.uv.x) * t, a.uv.y + (b.uv.y - a.uv.y) * t}
    };
}

void epr::render::Render::process_mesh(epr::geometry::Triangle &triangle, epr::spatial::Camera &camera, epr::graphics::Viewport &viewport, epr::geometry::Vertex *triangle_vertex, float fov, float aspect_x, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines) {
    // view distance culling
    int out_view_count = 0;

    for (int i = 0; i < 3; i++) {
        if (triangle.vertex[i].position.z < camera.view_distance) out_view_count++;
    }

    if (out_view_count == 3) return;

    // backface culling
    epr::math::Vector3 normal = triangle.normal();
    if (triangle.center().dot(normal) > 0) return;

    // clipping
    int triangle_vertex_count = 0;

    for (int i = 0; i < 3; i++) {
        epr::geometry::Vertex &current = triangle.vertex[i];
        epr::geometry::Vertex &next = triangle.vertex[(i + 1) % 3];

        bool current_inside = current.position.z <= camera.near;
        bool next_inside = next.position.z <= camera.near;

        if (current_inside && next_inside) {
            triangle_vertex[triangle_vertex_count] = next;
            triangle_vertex_count++;
        } else if (current_inside && !next_inside) {
            triangle_vertex[triangle_vertex_count] = intersect(current, next, camera.near);
            triangle_vertex_count++;
        } else if (!current_inside && next_inside) {
            triangle_vertex[triangle_vertex_count] = intersect(current, next, camera.near);
            triangle_vertex_count++;
            triangle_vertex[triangle_vertex_count] = next;
            triangle_vertex_count++;
        }
    }

    for (int i = 1; i + 1 < triangle_vertex_count; i++) {
        epr::geometry::Vertex triangle_fan[3] = {triangle_vertex[0], triangle_vertex[i], triangle_vertex[i + 1]};
        process_rasterize(triangle_fan, triangle.external_texture, fov, viewport, aspect_x, z_buffer, scanlines);
    }
}