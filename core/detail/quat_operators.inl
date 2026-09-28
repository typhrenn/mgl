#pragma once

#include "../quat.hpp"

namespace mgl {
    template <typename T>
    constexpr inline quat<T> operator*(quat<T> q1, quat<T> q2) noexcept {
        quat<T> res;

        res.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
        res.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
        res.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
        res.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;

        return res;
    }
}
