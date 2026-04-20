#ifndef EPR_RENDER_SCANLINES_HPP
#define EPR_RENDER_SCANLINES_HPP

#include <memory>

namespace epr::render {
    struct ScanlinesData {
        int min_x = 100000000, max_x = 0;
        float z1 = 0.0f, z2 = 0.0f;
        float u1, u2, v1, v2;
    };

    struct Scanlines {
        Scanlines(int h) :
            data(std::make_unique <ScanlinesData[]> (h)),
            h(h)
        {}

        ScanlinesData &at(int y) {
            return data[y];
        }

        void clear() {
            for (int i = 0; i < h; i++) {
                at(i) = ScanlinesData{};
            }
        }
    private:
        std::unique_ptr <ScanlinesData[]> data;
        int h;
    };
}

#endif