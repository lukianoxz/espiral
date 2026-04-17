#include <epr/espiral.hpp>
#include <chrono>

int main() {
    int screen_w = 110, screen_h = 70;
    epr::graphics::Display disp(screen_w, screen_h);
    epr::graphics::Viewport viewport(screen_w, screen_h);

    epr::render::Render render;
    epr::render::RenderData render_data(screen_w, screen_h);

    std::string whysoserios_string = epr::graphics::load_image("../utils/images/whysoserios.txt");
    epr::graphics::Texture whysoserios_texture = epr::graphics::Texture::load(whysoserios_string);
    epr::graphics::Texture inverse_whysoserios_texture = whysoserios_texture.inverse();

    epr::scene::Node node;

    node.mesh = epr::geometry::mesh::generate_quad({0, 0, -2}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture);
    node.add_mesh(epr::geometry::mesh::generate_quad({{-1, 0, -1}, {0, 1.57f, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{0, 0, 0}, {0, 3.14f, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{1, 0, -1}, {0, -1.57f, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{0, -1, -1}, {-1.57f, 0, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{0, 1, -1}, {1.57f, 0, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, -2.5f, 0}, {-1.57f, 0, 0}}, {5, 5}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, 2.5f, 0}, {1.57f, 0, 0}}, {5, 5}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, 0, -2.5f}, {0, 0, 0}}, {5, 5}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, 0, 2.5f}, {0, 3.14f, 0}}, {5, 5}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{-2.5f, 0, 0}, {0, 1.57f, 0}}, {5, 5}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{2.5f, 0, 0}, {0, -1.57f, 0}}, {5, 5}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    std::vector <epr::geometry::Triangle> mesh;
    bool running = true;

    epr::spatial::Camera cam;
    cam.fov = 2.1f;
    cam.near = -0.1f;
    cam.view_distance = -40;

    auto prev_frame = std::chrono::high_resolution_clock::now();

    while (running) {
        auto actual_frame = std::chrono::high_resolution_clock::now();
        std::chrono::duration <float> duration = actual_frame - prev_frame;
        float delta = duration.count();

        int c;
        if ((c = epr::input::getch()) != EOF) {
            switch (c) {
                case 'w': epr::logic::motion::Move(epr::logic::motion::direction::FORWARD, cam.origin, 3.2f, delta); break;
                case 's': epr::logic::motion::Move(epr::logic::motion::direction::BACKWARD, cam.origin, 3.2f, delta); break;
                case 'a': epr::logic::motion::Move(epr::logic::motion::direction::LEFT, cam.origin, 3.2f, delta); break;
                case 'd': epr::logic::motion::Move(epr::logic::motion::direction::RIGHT, cam.origin, 3.2f, delta); break;
                case 'j': cam.origin.rotation.rotation.y += 1.6f * delta; break;
                case 'l': cam.origin.rotation.rotation.y -= 1.6f * delta; break;
                case 'i': cam.origin.rotation.rotation.x += 1.6f * delta; break;
                case 'k': cam.origin.rotation.rotation.x -= 1.6f * delta; break;
                case 'q': running = false; break;
            }
        }

        std::cout << "FPS: " << 1.0f / delta << "\n";

        prev_frame = actual_frame;

        mesh = node.to_world();

        render.render_mesh(mesh, cam, viewport, render_data);
        disp.draw_viewport(0, 0, viewport);
        disp.show();
    }

    return 0;
}