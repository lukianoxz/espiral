#ifndef EPR_GRAPHICS_TEXTURE_HPP
#define EPR_GRAPHICS_TEXTURE_HPP

#include <epr/graphics/core/rgba.hpp>
#include <vector>
#include <string>

namespace epr::graphics {
    struct Texture {
        std::vector <epr::graphics::rgba> data;
        int size_x, size_y;

        Texture() = default;
        
        Texture(int size_x, int size_y) :
            data(size_x * size_y, epr::graphics::rgba{}),
            size_x(size_x),
            size_y(size_y)
        {}

        epr::graphics::rgba get(float u, float v) {
            return at(u, v);
        }

        void set(float u, float v, const epr::graphics::rgba &new_color) {
            at(u, v) = new_color;
        }

        static Texture load(std::string &texture);

        Texture inverse() {
            Texture temp_texture(size_x, size_y);

            for (int i = 0; i < size_y; i++) {
                for (int j = 0; j < size_x; j++) {
                    int inverse_i = size_y - 1 - i;
                    int inverse_j = size_x - 1 - j;

                    temp_texture.data[i * size_x + j] = data[inverse_i * size_x + inverse_j];
                }
            }

            return temp_texture;
        }
    private:
        inline epr::graphics::rgba &at(float u, float v) {
            int y = (int)(v * (float)size_y);
            int x = (int)(u * (float)size_x);

            y = y >= size_y ? size_y - 1 : y;
            x = x >= size_x ? size_x - 1 : x;
            
            return data[y * size_x + x];
        }
    };
}

#endif