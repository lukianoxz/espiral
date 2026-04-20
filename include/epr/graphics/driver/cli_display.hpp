#ifndef EPR_GRAPHICS_DRIVER_CLI_DISPLAY_HPP
#define EPR_GRAPHICS_DRIVER_CLI_DISPLAY_HPP

#include <epr/graphics/core/rgba.hpp>
#include <epr/graphics/core/viewport.hpp>
#include <vector>
#include <string>
#include <unistd.h>

namespace epr::graphics {
    struct PixelDisplay {
        epr::graphics::rgba up, down;

        void to_ansi(std::string &out, bool with_down) {
            out += "\033[38;2;" + std::to_string(up.r) + ";" + std::to_string(up.g) + ";" + std::to_string(up.b) + "m";
            if (with_down) out += "\033[48;2;" + std::to_string(down.r) + ";" + std::to_string(down.g) + ";" + std::to_string(down.b) + "m";
            out += "▀";
        }
    };

    class Display {
    public:
        Display(int w, int h) :
            screen(w * (h / 2 + h % 2)),
            w(w),
            h(h) {
            printf("\033[?25l"); // make cursor invisible
        }

        void draw_pixel(int x, int y, epr::graphics::rgba color);
        void draw_viewport(int x, int y, epr::graphics::Viewport &viewport);
        void show();

        void clear() {
            for (int i = 0; i < (h * w) / 2; i++) {
                screen[i].up = epr::graphics::rgba{};
                screen[i].down = epr::graphics::rgba{};
            }
        }

        ~Display() {
            printf("\033[?25h\033[0m"); // make cursor visible and reset all modes
        }
    private:
        std::vector <PixelDisplay> screen;
        std::string out_buffer;
        int w, h;

        epr::graphics::rgba *at(int x, int y);
    };
}

#endif