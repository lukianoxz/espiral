#ifndef EPR_GRAPHICS_RGBA_HPP
#define EPR_GRAPHICS_RGBA_HPP

#include <cstdint>

namespace epr::graphics {
    struct rgba {
        uint8_t r = 0, g = 0, b = 0, a = 255;

        rgba operator + (const rgba &other) const {
            return {
                (uint8_t)((r + other.r > 255) ? 255 : r + other.r),
                (uint8_t)((g + other.g > 255) ? 255 : g + other.g),
                (uint8_t)((b + other.b > 255) ? 255 : b + other.b)
            };
        }

        rgba operator - (const rgba &other) const {
            return {
                (uint8_t)((r - other.r < 0) ? 0 : r - other.r),
                (uint8_t)((g - other.g < 0) ? 0 : g - other.g),
                (uint8_t)((b - other.b < 0) ? 0 : b - other.b)
            };
        }
    };
}

#endif