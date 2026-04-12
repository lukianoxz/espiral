#ifndef EPR_MATH_VECTOR3_HPP
#define EPR_MATH_VECTOR3_HPP

#include <cmath>

namespace epr::math {
    struct Vector3 {
        float x = 0.0f, y = 0.0f, z = 0.0f;

        Vector3 operator + (const Vector3 &other) const {
            return {
                x + other.x,
                y + other.y,
                z + other.z
            };
        }
    
        Vector3 operator - (const Vector3 &other) const {
            return {
                x - other.x,
                y - other.y,
                z - other.z
            };
        }

        Vector3 operator * (float f) const {
            return {
                x * f,
                y * f,
                z * f
            };
        }

        Vector3 operator / (float f) const {
            if (f == 0) return {0, 0, 0};
            return {
                x / f,
                y / f,
                z / f
            };
        }

        Vector3 &operator += (const Vector3 &other) {
            x += other.x;
            y += other.y;
            z += other.z;

            return *this;
        }
    
        Vector3 &operator -= (const Vector3 &other) {
            x -= other.x;
            y -= other.y;
            z -= other.z;

            return *this;
        }

        float dot(const Vector3 &other) const {
            return x * other.x + y * other.y + z * other.z;
        }

        float module() const {
            return std::sqrt(dot(*this));
        }

        Vector3 normalize() const {
            return *this / module();
        }

        Vector3 cross(const Vector3 &other) const {
            return {
                y * other.z - z * other.y,
                z * other.x - x * other.z,
                x * other.y - y * other.x
            };
        }
    };
}

#endif