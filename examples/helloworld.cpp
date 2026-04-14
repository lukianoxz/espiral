#include <epr/espiral.hpp>

int main() {
    int screen_w = 80, screen_h = 40;
    epr::graphics::Display disp(screen_w, screen_h);
    epr::graphics::Viewport viewport(screen_w, screen_h);

    epr::render::Render render;
    epr::render::Scanlines scanline(screen_h);
    epr::render::ZBuffer z_buffer(screen_w, screen_h);

    std::vector <epr::geometry::Triangle> mesh;

    epr::geometry::Triangle trig;
    trig.vertex[0].position = {0, 1, -3};
    trig.vertex[1].position = {-1, -1, -3};
    trig.vertex[2].position = {1, -1, -3};

    trig.vertex[0].uv = {0, 1};
    trig.vertex[1].uv = {1, 1};
    trig.vertex[2].uv = {1, 0};

    trig.external_texture = epr::graphics::Texture(3);

    trig.external_texture.data[0] = epr::graphics::rgba{255, 0, 0, 255};
    trig.external_texture.data[1] = epr::graphics::rgba{0, 255, 0, 255};
    trig.external_texture.data[2] = epr::graphics::rgba{255, 255, 0, 255};
    trig.external_texture.data[3] = epr::graphics::rgba{255, 255, 0, 55};
    trig.external_texture.data[4] = epr::graphics::rgba{255, 0, 255, 255};
    trig.external_texture.data[5] = epr::graphics::rgba{0, 255, 255, 255};

    mesh.push_back(trig);

    epr::spatial::Camera cam;
    cam.fov = 2.1f;
    cam.near = -0.1f;
    cam.view_distance = -40;

    render.render_mesh(mesh, cam, viewport, z_buffer, scanline);
    disp.draw_viewport(0, 0, viewport);
    disp.show();

    return 0;
}