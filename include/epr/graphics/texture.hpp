#ifndef EPR_GRAPHICS_TEXTURE_HPP
#define EPR_GRAPHICS_TEXTURE_HPP

#include <epr/graphics/rgba.hpp>
#include <vector>
#include <string>

namespace epr::graphics {
    struct Texture {
        std::vector <epr::graphics::rgba> data;
        int size;

        Texture() = default;
        
        Texture(int size) :
            data((std::size_t)size * size, epr::graphics::rgba{}),
            size(size)
        {}

        epr::graphics::rgba get(float u, float v) {
            return at(u, v);
        }

        void set(float u, float v, const epr::graphics::rgba &new_color) {
            at(u, v) = new_color;
        }

        static Texture load(std::string &texture);
    private:
        inline epr::graphics::rgba &at(float u, float v) {
            int y = (int)(v * (float)size);
            int x = (int)(u * (float)(size));

            y = y >= size ? size - 1 : y;
            x = x >= size ? size - 1 : x;
            
            return data[y * size + x];
        }
    };
}

#endif