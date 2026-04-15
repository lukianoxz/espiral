#include <epr/espiral.hpp>

int main() {
    int screen_w = 110, screen_h = 70;
    epr::graphics::Display disp(screen_w, screen_h);
    epr::graphics::Viewport viewport(screen_w, screen_h);

    epr::render::Render render;
    epr::render::RenderData render_data(screen_w, screen_h);

    std::string tex = "2;X"
    "255000000255""000255000255"
    "000000255255""255000255255"
    ;

    epr::scene::Node node;

    node.mesh = epr::geometry::mesh::generate_quad({0, 0, -6}, tex);
    node.add_mesh(epr::geometry::mesh::generate_quad({{-1, 0, -5}, {0, 1.57, 0}}, tex));
    std::vector <epr::geometry::Triangle> mesh;
    bool running = true;

    epr::spatial::Camera cam;
    cam.fov = 2.1f;
    cam.near = -0.1f;
    cam.view_distance = -40;

    while (running) {
        int c;
        while ((c = epr::input::getch()) != EOF) {
            switch (c) {
                case 'w':
                    epr::logic::motion::Move(epr::logic::motion::direction::FORWARD, cam.origin, 0.2f, 1.0f);
                    break;
                case 's':
                    epr::logic::motion::Move(epr::logic::motion::direction::BACKWARD, cam.origin, 0.2f, 1.0f);
                    break;
                case 'a':
                    epr::logic::motion::Move(epr::logic::motion::direction::LEFT, cam.origin, 0.2f, 1.0f);
                    break;
                case 'd':
                    epr::logic::motion::Move(epr::logic::motion::direction::RIGHT, cam.origin, 0.2f, 1.0f);
                    break;
                case 'j':
                    cam.origin.rotation.rotation.y += 0.1f;
                    break;
                case 'l':
                    cam.origin.rotation.rotation.y -= 0.1f;
                    break;
                case 'q':
                    running = false;
                    break;
            }
        }

        mesh = node.to_world();

        render.render_mesh(mesh, cam, viewport, render_data);
        disp.draw_viewport(0, 0, viewport);
        disp.show();
    }

    return 0;
}