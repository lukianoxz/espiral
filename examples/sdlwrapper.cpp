#include <epr/espiral.hpp>
#include <algorithm>

#ifndef EPR_HAS_SDL3
    #define WARNING std::cerr << "Error, you dont have sdl3\n"; std::exit(-1);
#else
    #define WARNING
#endif

#define EPR_WIDTH 640
#define EPR_HIGH 360

int main() {
    WARNING
    epr::graphics::SDLWrapper sdl_window(SDL_INIT_VIDEO, EPR_WIDTH, EPR_HIGH, "espiral", 2);

    epr::graphics::Viewport viewport(EPR_WIDTH, EPR_HIGH);

    epr::render::Render render;
    epr::render::RenderData render_data(EPR_WIDTH, EPR_HIGH);

    std::string whysoserios_string = epr::system::io::load_file("../utils/images/whysoserios.txt");
    epr::graphics::Texture whysoserios_texture = epr::graphics::Texture::load(whysoserios_string);
    epr::graphics::Texture inverse_whysoserios_texture = whysoserios_texture.inverse();

    epr::scene::Node node;

    node.mesh = epr::geometry::mesh::generate_quad({{0, 0, -2}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture);
    node.add_mesh(epr::geometry::mesh::generate_quad({{-1, 0, -1}, {1.57f, 0, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{0, 0, 0}, {3.14f, 0, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{1, 0, -1}, {-1.57f, 0, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{0, -1, -1}, {0, -1.57f, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_quad({{0, 1, -1}, {0, 1.57f, 0}}, {1, 1}, whysoserios_texture, inverse_whysoserios_texture));
    
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, -20, 0}, {0, -1.57f, 0}}, {40, 40}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, 20, 0}, {0, 1.57f, 0}}, {40, 40}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, 0, -20}, {0, 0, 0}}, {40, 40}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{0, 0, 20}, {3.14f, 0, 0}}, {40, 40}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{-20, 0, 0}, {1.57f, 0, 0}}, {40, 40}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    node.add_mesh(epr::geometry::mesh::generate_plane({{20, 0, 0}, {-1.57f, 0, 0}}, {40, 40}, {5, 5}, whysoserios_texture, inverse_whysoserios_texture));
    std::vector <epr::geometry::Triangle> mesh;
    bool running = true;

    epr::spatial::Camera cam;
    cam.fov = 2.1f;
    cam.near = -0.1f;
    cam.view_distance = -40;

    auto prev_frame = std::chrono::high_resolution_clock::now();

    SDL_Event sdl_event;
    bool is_running = true;
    float mouse_sensi = 0.01f;

    bool mouse_cap = true;
    auto mouse_cap_frame = std::chrono::high_resolution_clock::now();
    SDL_SetWindowRelativeMouseMode(sdl_window.sdl_window, mouse_cap);

    while (is_running) {
        mesh = node.to_world();

        auto actual_frame = std::chrono::high_resolution_clock::now();
        std::chrono::duration <float> duration = actual_frame - prev_frame;
        float delta = duration.count();

        while (SDL_PollEvent(&sdl_event)) {
            if (sdl_event.type == SDL_EVENT_QUIT) is_running = false;
            if (sdl_event.key.key == SDLK_ESCAPE) {
                 std::chrono::duration <float> elapsed = actual_frame - mouse_cap_frame;

                if (elapsed.count() > 0.3f) {
                    mouse_cap = !mouse_cap;
                    SDL_SetWindowRelativeMouseMode(sdl_window.sdl_window, mouse_cap);
                    mouse_cap_frame = actual_frame;
                }
            }

            if (sdl_event.type == SDL_EVENT_MOUSE_MOTION && mouse_cap) {
                cam.origin.rotation.yaw -= sdl_event.motion.xrel * mouse_sensi;
                cam.origin.rotation.pitch = std::clamp(cam.origin.rotation.pitch - sdl_event.motion.yrel * mouse_sensi, -1.54f, 1.54f);
            }
        }

        int num_keys;
        const bool* key_state = SDL_GetKeyboardState(&num_keys);

        if (key_state[SDL_SCANCODE_W]) epr::logic::motion::Move(epr::logic::motion::direction::FORWARD, cam.origin, 3.2f, delta);
        if (key_state[SDL_SCANCODE_S]) epr::logic::motion::Move(epr::logic::motion::direction::BACKWARD, cam.origin, 3.2f, delta);
        if (key_state[SDL_SCANCODE_A]) epr::logic::motion::Move(epr::logic::motion::direction::LEFT, cam.origin, 3.2f, delta);
        if (key_state[SDL_SCANCODE_D]) epr::logic::motion::Move(epr::logic::motion::direction::RIGHT, cam.origin, 3.2f, delta);
        if (key_state[SDL_SCANCODE_SPACE]) epr::logic::motion::Move(epr::logic::motion::direction::UP, cam.origin, 3.2f, delta);
        if (key_state[SDL_SCANCODE_LSHIFT]) epr::logic::motion::Move(epr::logic::motion::direction::DOWN, cam.origin, 3.2f, delta);

        prev_frame = actual_frame;

        render.render_mesh(mesh, cam, viewport, render_data);
        sdl_window.show_viewport(viewport);
    }
    SDL_SetWindowRelativeMouseMode(sdl_window.sdl_window, false);

    return 0;
}