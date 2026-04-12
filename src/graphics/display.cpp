#include <epr/graphics/display.hpp>

epr::graphics::rgba *epr::graphics::Display::at(int x, int y) {
    if (y < 0 || y >= h || x < 0 || x >= w) return nullptr;

    bool pixel_down = y % 2;
    int real_y = (y / 2);
    int offset = real_y * w + x;

    return !pixel_down ? &screen[offset].up : &screen[offset].down;
}

void epr::graphics::Display::draw_pixel(int x, int y, epr::graphics::rgba color) {
    epr::graphics::rgba *target = at(x, y);
    
    if (!target) return;

    *target = color;
}

void epr::graphics::Display::draw_viewport(int x, int y, epr::graphics::Viewport &viewport) {
    for (int i = 0; i < viewport.h; i++) {
        for (int j = 0; j < viewport.w; j++) {
            draw_pixel(x + j, y + i, *viewport.at(j, i));
        }
    }
}

void epr::graphics::Display::show() {
    out_buffer.clear();
    out_buffer += "\033[H";
    int screen_h = h / 2 + h % 2;

    for (int i = 0; i < screen_h; i++) {
        for (int j = 0; j < w; j++) {
            screen[i * w + j].to_ansi(out_buffer, !(i + (h % 2) == screen_h));
        }
        out_buffer += "\n\033[0m";
    }

    write(1, out_buffer.c_str(), out_buffer.size());
}