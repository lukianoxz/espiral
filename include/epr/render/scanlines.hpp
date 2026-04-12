#ifndef EPR_RENDER_SCANLINES_HPP
#define EPR_RENDER_SCANLINES_HPP

#include <memory>

namespace epr::render {
    struct ScanlinesData {
        int min_x = 0, max_x = 0;
    };

    struct Scanlines {
        Scanlines(int h) :
            data(std::make_unique <ScanlinesData[]> (h)),
            h(h)
        {}

        ScanlinesData &at(int y) {
            return data[y];
        }
    private:
        std::unique_ptr <ScanlinesData[]> data;
        int h;
    };
}

#endif