#pragma once

#include <cmath>
#include "../core/quat.hpp"
#include "vec_func.hpp"
#include "../gtc/constants.hpp"

namespace mgl {
    template <typename T>
    inline Quat<T> Quat<T>::single_axis_quat(const vec<3, T> &axis, radian<T> rad) noexcept {
        vec<3, T> norm_axis = mgl::normalize(axis);

        T half_angle = static_cast<T>(rad) * static_cast<T>(0.5);
        T c = std::cos(half_angle);
        T s = std::sin(half_angle);

        return Quat<T>{s * norm_axis.x, s * norm_axis.y, s * norm_axis.z, c};
    }

    // quaternion from 3 axes
    template <typename T>
    inline Quat<T> Quat<T>::full_axis_quat(const vec<3, T> &rot) noexcept {
        return single_axis_quat(x_axis(), rot.x)
             * single_axis_quat(y_axis(), rot.y)
             * single_axis_quat(z_axis(), rot.z);
    }

    // quaternion dot product
    template <typename T>
    constexpr inline T Quat<T>::dot(const Quat<T> &b) const noexcept {
        return (x * b.x) + (y * b.y) + (z * b.z) + (w * b.w);
    }

    // quaternion normalization
    template <typename T>
    inline Quat<T>& Quat<T>::normalize() noexcept {
        T norm = (x * x) + (y * y) + (z * z) + (w * w);

        if (norm == static_cast<T>(0)) {
            *this = identity_quat;
            return *this;
        }

        T inv_norm = static_cast<T>(1) / std::sqrt(norm);

        x *= inv_norm;
        y *= inv_norm;
        z *= inv_norm;
        w *= inv_norm;
        
        return *this;
    }

    // quaternion conjugation
    template <typename T>
    constexpr inline Quat<T>& Quat<T>::conjugate() noexcept {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    // quaternion inverse
    template <typename T>
    constexpr inline Quat<T>& Quat<T>::inverse() noexcept {
        T norm = (x * x) + (y * y) + (z * z) + (w * w);

        if (norm == static_cast<T>(0)) {
            *this = identity_quat;
            return *this;
        }

        T inv_norm = static_cast<T>(1.0f) / norm;
        
        conjugate();
        
        x *= inv_norm;
        y *= inv_norm;
        z *= inv_norm;
        w *= inv_norm;

        return *this;
    }

    // quaternion spherical interpolation
    template <typename T>
    inline Quat<T>& Quat<T>::slerp(const Quat<T> &b, T t) noexcept {
        T cos_theta = dot(b);
        Quat<T> dest = b;

        if (cos_theta < static_cast<T>(0)) {
            cos_theta = -cos_theta;
            dest = Quat<T>{-b.x, -b.y, -b.z, -b.w};
        }

        if (cos_theta > static_cast<T>(1) - epsilon<T>()) {
            x += t * (dest.x - x);
            y += t * (dest.y - y);
            z += t * (dest.z - z);
            w += t * (dest.w - w);
            return normalize();
        }

        T theta = std::acos(cos_theta);
        T sin_theta = std::sin(theta);

        T inv_sin = static_cast<T>(1) / sin_theta;

        T w1 = std::sin((static_cast<T>(1) - t) * theta) * inv_sin;
        T w2 = std::sin(t * theta) * inv_sin;

        x = (w1 * x) + (w2 * dest.x);
        y = (w1 * y) + (w2 * dest.y);
        z = (w1 * z) + (w2 * dest.z);
        w = (w1 * w) + (w2 * dest.w);

        return *this;
    }

	template <typename T>
	constexpr inline vec3 Quat<T>::rotate(const vec3 &v) const noexcept {
		vec3 qv = vec3{x, y, z};
		vec3 t = cross(qv, v) * 2.0f;

		return v + (t * w) + cross(qv, t);
	}

	template <typename T>
    inline vec<3, radian<>> Quat<T>::quat_to_euler() const noexcept {
        return vec<3, radian<>>{ 
            atan2(2.0f * (w * x + y * z), 1.0f - 2.0f * (x * x + y * y)),
            asin(clamp(2 * (w * y - z * x), static_cast<T>(-1), static_cast<T>(1))),
            atan2(2.0f * (w * z + x * y), 1.0f - 2.0f * (y * y + z * z))
        };
    }
}