#ifndef EPR_CORE_SPATIAL_CAMERA_HPP
#define EPR_CORE_SPATIAL_CAMERA_HPP

#include <epr/core/spatial/transform/transform3.hpp>

namespace epr::spatial {
    struct Camera {
        epr::spatial::Transform3 origin;
        float fov;
        float near;
        float view_distance;
    };
}

#endif