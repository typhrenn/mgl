#pragma once

#include <cmath>
#include "../core/quat.hpp"
#include "../core/types.hpp"
#include "../core/vec.hpp"
#include "vec_func.hpp"
#include "../constants/constants.hpp"

namespace mgl {
	// from radians
    template <typename T = float>
    inline quat<T> single_axis_quat(const vec<3, T> &axis, radian<T> rad) noexcept {
        vec<3, T> norm_axis = normalize(axis);

        T half_angle = static_cast<T>(rad) * static_cast<T>(0.5);
        T c = std::cos(half_angle);
        T s = std::sin(half_angle);

        return quat<T>{s * norm_axis.x, s * norm_axis.y, s * norm_axis.z, c};
    }

    // quaternion from 3 axes
    template <typename T = float>
    inline quat<T> full_axis_quat(const vec<3, T> &rot) noexcept {
        return single_axis_quat(x_axis(), rot.x)
             * single_axis_quat(y_axis(), rot.y)
             * single_axis_quat(z_axis(), rot.z);
    }

    // quaternion dot product
    template <typename T>
    constexpr inline T dot(const quat<T> &a, const quat<T> &b) noexcept {
        return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
    }

    // quaternion normalization
    template <typename T>
    inline quat<T> normalize(const quat<T> &q) noexcept {
        T norm = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);

        // fallback
        if (norm == static_cast<T>(0)) return identity_quat;

        T inv_norm = static_cast<T>(1) / std::sqrt(norm);

        return quat<T>{
            q.x * inv_norm,
            q.y * inv_norm,
            q.z * inv_norm,
            q.w * inv_norm
        };
    }

    // quaternion conjugation
    template <typename T>
    constexpr inline quat<T> conjugate(const quat<T> &q) noexcept {
        return quat<T>{
            -q.x,
            -q.y,
            -q.z,
            q.w
        };
    }

    // quaternion inverse
    template <typename T>
    constexpr inline quat<T> inverse(const quat<T> &q) noexcept {
        T norm = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);

        if (norm == static_cast<T>(0)) return identity_quat;

        T inv_norm = static_cast<T>(1.0f) / norm;
        quat<T> cq = conjugate(q);

        return quat<T>{
            cq.x * inv_norm,
            cq.y * inv_norm,
            cq.z * inv_norm,
            cq.w * inv_norm
        };
    }

    // quaternion spherical interpolation
    template <typename T>
    inline quat<T> slerp(const quat<T> &a, const quat<T> &b, T t) noexcept {
        T cos_theta = dot(a, b);
        quat<T> dest = b;

        if (cos_theta < static_cast<T>(0)) {
            cos_theta = -cos_theta;
            dest = quat<T>{-b.x, -b.y, -b.z, -b.w};
        }

        if (cos_theta > static_cast<T>(1) - epsilon<T>()) {
            return normalize(quat<T>{
                a.x + t * (dest.x - a.x),
                a.y + t * (dest.y - a.y),
                a.z + t * (dest.z - a.z),
                a.w + t * (dest.w - a.w),
            });
        }

        T theta = std::acos(cos_theta);
        T sin_theta = std::sin(theta);

        T inv_sin = static_cast<T>(1) / sin_theta;

        T w1 = std::sin((static_cast<T>(1) - t) * theta) * inv_sin;
        T w2 = std::sin(t * theta) * inv_sin;

        return quat<T>{
            (w1 * a.x) + (w2 * dest.x),
            (w1 * a.y) + (w2 * dest.y),
            (w1 * a.z) + (w2 * dest.z),
            (w1 * a.w) + (w2 * dest.w)
        };
    }

	template <typename T>
	constexpr inline vec3 rotate(const quat<T> &q, const vec3 &v) noexcept {
		vec3 qv = vec3{q.x, q.y, q.z};
		vec3 t = cross(qv, v) * 2.0f;

		return v + (t * q.w) + cross(qv, t);
	}

	template <typename T>
    inline vec<3, radian<>> quat_to_euler(const quat<T> &q) noexcept {
        return vec<3, radian<>>{ 
            atan2(2.0f * (q.w * q.x + q.y * q.z), 1.0f - 2.0f * (q.x * q.x + q.y * q.y)),
            asin(clamp(2 * (q.w * q.y - q.z * q.x), static_cast<T>(-1), static_cast<T>(1))),
            atan2(2.0f * (q.w * q.z + q.x * q.y), 1.0f - 2.0f * (q.y * q.y + q.z * q.z))
        };
    }
}