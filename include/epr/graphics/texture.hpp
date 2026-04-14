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
            data((std::size_t)size * ((std::size_t)size + 1) / 2, epr::graphics::rgba{}),
            size(size)
        {}

        epr::graphics::rgba get(float u, float v) {
            return at(u, v);
        }

        void set(float u, float v, const epr::graphics::rgba &new_color) {
            at(u, v) = new_color;
        }

        void load(std::string texture);
    private:
        inline epr::graphics::rgba &at(float u, float v) {
            int y = (int)(v * (float)size);
            int x = (int)(u * (float)(y + 1));
            
            return data[(std::size_t)(y * (y + 1) / 2 + x)];
        }
    };
}

#endif