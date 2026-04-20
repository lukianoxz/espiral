#ifndef EPR_CORE_SPATIAL_RAY_HPP
#define EPR_CORE_SPATIAL_RAY_HPP

#include <epr/core/math/math.hpp>
#include <epr/core/spatial/transform/transform3.hpp>
#include <epr/world/geometry/triangle/triangle.hpp>

namespace epr::spatial {
    struct RayHit {
        float distance;
        float u, v;
        epr::math::Vector3 normal;
    };
    struct Ray {
        Ray(epr::math::Vector3 position) :
            position(position)
        {}

        void look_at(epr::math::Vector3 target) {
            direction = (target - position).normalize();
        }

        bool intersect(epr::geometry::Triangle &triangle, RayHit &hit) {
            const float EPSILON = 0.0001f;

            epr::math::Vector3 edge1 = triangle.vertex[1].position - triangle.vertex[0].position;
            epr::math::Vector3 edge2 = triangle.vertex[2].position - triangle.vertex[0].position;
            epr::math::Vector3 cross_direction = direction.cross(edge2);
            
            float determinant = edge1.dot(cross_direction);

            if (determinant > -EPSILON && determinant < EPSILON) return false;

            epr::math::Vector3 vertex_distance = position - triangle.vertex[0].position;

            float u = vertex_distance.dot(cross_direction) / determinant;
            if (u < 0.0f || u > 1.0f) return false;

            epr::math::Vector3 v_cross = vertex_distance.cross(edge1);

            float v = direction.dot(v_cross) / determinant;
            if (v < 0.0f || u + v > 1.0f) return false;

            float t = edge2.dot(v_cross) / determinant;
            if (t < EPSILON) return false;

            hit.distance = t;
            hit.u = u;
            hit.v = v;
            hit.normal = edge1.cross(edge2).normalize();

            if (hit.normal.dot(direction) > 0) {
                hit.normal = hit.normal * -1.0f;
            }

            return true;
        }
    private:
        epr::math::Vector3 position;
        epr::math::Vector3 direction;
    };
}

#endif