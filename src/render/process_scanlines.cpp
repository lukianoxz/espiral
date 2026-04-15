#include <epr/render/render.hpp>

#include <cmath>

void epr::render::Render::process_scanlines(epr::geometry::Vertex *vertex, epr::graphics::Texture &external_texture, epr::graphics::Viewport &viewport, epr::render::ZBuffer &z_buffer, epr::render::Scanlines &scanlines) {
    scanlines.clear();
    int min_y = vertex[0].position.y, max_y = vertex[0].position.y;

    for (int i = 0; i < 3; i++) {
        int vertex_y = (int)vertex[i].position.y;
        min_y = (vertex_y < min_y) ? vertex_y : min_y;
        max_y = (vertex_y > max_y) ? vertex_y : max_y;
    }

    min_y = min_y < 0 ? 0 : min_y;
    max_y = max_y >= viewport.h ? viewport.h - 1 : max_y;

    for (int i = 0; i < 3; i++) {
        epr::geometry::Vertex vtx1 = vertex[i];
        epr::geometry::Vertex vtx2 = vertex[(i + 1) % 3];

        float dx = vtx2.position.x - vtx1.position.x;
        float dy = vtx2.position.y - vtx1.position.y;
        float dz = vtx2.position.z - vtx1.position.z;
        float du = vtx2.uv.x - vtx1.uv.x;
        float dv = vtx2.uv.y - vtx1.uv.y;

        float dist = std::max(std::abs(dx), std::abs(dy));
        
        if ((int)dist < 1) continue;

        for (int j = 0; j <= (int)dist; j++) {
            float t = ((float)j / dist);

            float x = vtx1.position.x + dx * t;
            float y = vtx1.position.y + dy * t;
            float z = vtx1.position.z + dz * t;
            float u = vtx1.uv.x + du * t;
            float v = vtx1.uv.y + dv * t;

            if (y < min_y || y > max_y) continue;

            int iy = (int)(y + 0.2f);

            if (iy < min_y || iy >= max_y) continue;
            epr::render::ScanlinesData &scanlines_data = scanlines.at(iy);

            float sz = z < 0.0001f ? 0.0001f : z; // safe z

            if (x < scanlines_data.min_x) {
                scanlines_data.min_x = x;
                scanlines_data.z1 = z;
                scanlines_data.u1 = u / sz;
                scanlines_data.v1 = v / sz;
            }
            if (x > scanlines_data.max_x) {
                scanlines_data.max_x = x;
                scanlines_data.z2 = z;
                scanlines_data.u2 = u / sz;
                scanlines_data.v2 = v / sz;
            }
        }
    }

    for (int i = min_y; i <= max_y; i++) {
        epr::render::ScanlinesData &current_scanline = scanlines.at(i);
        
        float dist_x = (float)(current_scanline.max_x - current_scanline.min_x);

        for (int j = current_scanline.min_x; j < current_scanline.max_x; j++) {
            float t = (float)(j - current_scanline.min_x) / dist_x;
            
            float dz = current_scanline.z2 - current_scanline.z1;
            float iz = current_scanline.z1 + dz * t; // interpolated z

            float inv_z = 1 / current_scanline.z1 + (1 / current_scanline.z2 - 1 / current_scanline.z1) * t;
            float iu = current_scanline.u1 + (current_scanline.u2 - current_scanline.u1) * t;
            float iv = current_scanline.v1 + (current_scanline.v2 - current_scanline.v1) * t;

            float correct_u = iu / inv_z;
            float correct_v = iv / inv_z;

            correct_u = (correct_u < 0.01f) ? 0.01f : (correct_u > 0.99f) ? 0.99f : correct_u;
            correct_v = (correct_v < 0.01f) ? 0.01f : (correct_v > 0.99f) ? 0.99f : correct_v;

            if (j < 0 || j >= viewport.w) continue;

            epr::render::ZBufferData &current_z_buffer = z_buffer.at(j, i);

            if (iz < current_z_buffer.z) {
                current_z_buffer.z = iz;
                current_z_buffer.color = external_texture.get(correct_u, correct_v);
            }
        }
    }
}