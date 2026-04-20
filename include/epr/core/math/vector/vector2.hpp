#ifndef EPR_CORE_MATH_VECTOR_VECTOR2_HPP
#define EPR_CORE_MATH_VECTOR_VECTOR2_HPP

namespace epr::math {
    struct Vector2 {
        float x = 0.0f, y = 0.0f;

        Vector2() = default;

        Vector2(float x, float y) :
            x(x),
            y(y)
        {}

        Vector2 operator + (const Vector2 &other) const {
            return {
                x + other.x,
                y + other.y
            };
        }
        Vector2 operator - (const Vector2 &other) const {
            return {
                x - other.x,
                y - other.y
            };
        }
    };

    struct Vector2i {
        int x = 0, y = 0;

        Vector2i() = default;

        Vector2i(int x, int y) :
            x(x),
            y(y)
        {}

        Vector2i operator + (const Vector2i &other) const {
            return {
                x + other.x,
                y + other.y
            };
        }
        Vector2i operator - (const Vector2i &other) const {
            return {
                x - other.x,
                y - other.y
            };
        }
    };
}

#endif