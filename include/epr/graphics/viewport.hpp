#ifndef EPR_GRAPHICS_VIEWPORT_HPP
#define EPR_GRAPHICS_VIEWPORT_HPP

#include <epr/graphics/rgba.hpp>
#include <memory>

namespace epr::graphics {
    struct Viewport {
        Viewport(int w, int h) :
            screen(std::make_unique <epr::graphics::rgba[]> (w * h)),
            w(w),
            h(h)
        {};

        void draw_pixel(int x, int y, epr::graphics::rgba color) {
            epr::graphics::rgba *target = at(x, y);
            if (!target) return;
            *target = color;
        }

        void clear() {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    *at(j, i) = epr::graphics::rgba{};
                }
            }
        }

        epr::graphics::rgba *at(int x, int y) {
            if (x < 0 || x >= w || y < 0 || y >= h) return nullptr;
            return &screen[y * w + x];
        }
        
        const int w, h;
    private:
        std::unique_ptr <epr::graphics::rgba[]> screen;
    };
}

#endif