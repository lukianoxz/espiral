#include <epr/espiral.hpp>

int main() {
    int screen_w = 80, screen_h = 40;
    epr::graphics::Display disp(screen_w, screen_h);
    epr::graphics::Viewport viewport(screen_w, screen_h);

    epr::render::Render render;
    epr::render::Scanlines scanline(screen_h);
    epr::render::ZBuffer z_buffer(screen_w, screen_h);

    std::vector <epr::geometry::Triangle> mesh;

    std::string tex = "2;X"
    "255000000255""000255000255"
    "000000255255""255000255255"
    ;

    epr::geometry::Triangle trig(tex);
    trig.vertex[0].position = {1, 1, -3};
    trig.vertex[1].position = {-1, 1, -3};
    trig.vertex[2].position = {-1, -1, -3};
    
    tex[2] = 'F';
    epr::geometry::Triangle trig2(tex);
    trig2.vertex[0].position = {-1, -1, -3};
    trig2.vertex[1].position = {1, -1, -3};
    trig2.vertex[2].position = {1, 1, -3};

    mesh.push_back(trig);
    mesh.push_back(trig2);

    epr::spatial::Camera cam;
    cam.fov = 2.1f;
    cam.near = -0.1f;
    cam.view_distance = -40;

    render.render_mesh(mesh, cam, viewport, z_buffer, scanline);
    disp.draw_viewport(0, 0, viewport);
    disp.show();

    return 0;
}