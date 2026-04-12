#ifndef EPR_RENDER_ZBUFFER_HPP
#define EPR_RENDER_ZBUFFER_HPP

#include <epr/graphics/rgba.hpp>
#include <memory>

namespace epr::render {
    struct ZBufferData {
        epr::graphics::rgba color;
        float z = 100000000.0f;
    };

    struct ZBuffer {
        ZBuffer(int w, int h) :
            data(std::make_unique <ZBufferData[]> (h * w)),
            w(w),
            h(h)
        {}

        ZBufferData &at(int x, int y) {
            return data[y * w + x];
        }

        void clear() {
            for (int i = 0; i < h; i++) {
                for (int j = 0; j < w; j++) {
                    at(j, i) = ZBufferData{};
                }
            }
        }
    private:
        std::unique_ptr <ZBufferData[]> data;
        int w, h;
    };
}

#endif