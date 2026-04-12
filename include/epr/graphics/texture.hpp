#ifndef EPR_GRAPHICS_TEXTURE_HPP
#define EPR_GRAPHICS_TEXTURE_HPP

#include <epr/graphics/rgba.hpp>
#include <memory>

namespace epr::graphics {
    struct Texture {
        std::unique_ptr <epr::graphics::rgba[]> data;
        int size;

        Texture() :
            data(nullptr),
            size(0)
        {}
        
        Texture(int size) :
            data(std::make_unique <epr::graphics::rgba[]> (size * (size + 1) / 2)),
            size(size)
        {}

        epr::graphics::rgba get(float u, float v) {
            return at(u, v);
        }

        void set(float u, float v, const epr::graphics::rgba &new_color) {
            at(u, v) = new_color;
        }
    private:
        inline epr::graphics::rgba &at(float u, float v) {
            int y = (int)(v * (float)size);
            int x = (int)(u * (float)(y + 1));

            return data[y * (y + 1) / 2 + x];
        }
    };
}

#endif