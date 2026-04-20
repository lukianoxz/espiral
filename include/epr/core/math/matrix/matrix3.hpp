#ifndef EPR_CORE_MATH_MATRIX_MATRIX3_HPP
#define EPR_CORE_MATH_MATRIX_MATRIX3_HPP

#include <epr/core/math/vector/vector3.hpp>

namespace epr::math {
    struct Matrix3 {
        float data[3][3] = {};

        static Matrix3 identity() {
            return { {
                    {1.0f, 0.0f, 0.0f},
                    {0.0f, 1.0f, 0.0f},
                    {0.0f, 0.0f, 1.0f}
            } };
        }

        Matrix3 operator * (const Matrix3 &other) const {
            Matrix3 temp;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        temp.data[i][j] += data[i][k] * other.data[k][j];
                    }
                }
            }

            return temp;
        };

        epr::math::Vector3 operator * (const epr::math::Vector3 &vector3) const {
            return {
                vector3.x * data[0][0] + vector3.y * data[0][1] + vector3.z * data[0][2],
                vector3.x * data[1][0] + vector3.y * data[1][1] + vector3.z * data[1][2],
                vector3.x * data[2][0] + vector3.y * data[2][1] + vector3.z * data[2][2]
            };
        }

        Matrix3 transpose() const {
            Matrix3 temp;

            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    temp.data[j][i] = data[i][j];
                }
            }

            return temp;
        }
    };
}

#endif