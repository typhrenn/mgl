#pragma once

#include <cmath>
#include "../core/quat.hpp"
#include "../core/types.hpp"
#include "vec_func.hpp"
#include "../gtc/constants.hpp"

namespace mgl {
    inline quat_f single_axis_quat(const vec3 &axis, radian<float> rad) noexcept {
        vec3 norm_axis = normalize(axis);

        float half_angle = rad * 0.5f;
        float c = std::cos(half_angle);
        float s = std::sin(half_angle);

        return quat_f{s * norm_axis.x, s * norm_axis.y, s * norm_axis.z, c};
    }

	// quaternion from 3 axes
    inline quat_f full_axis_quat(const vec3 &rot) noexcept {
        return single_axis_quat(x_axis(), rot.x)
             * single_axis_quat(y_axis(), rot.y)
             * single_axis_quat(z_axis(), rot.z);
    }

	// quaternion dot product
	inline float dot(const quat_f a, const quat_f b) noexcept {
		return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
	}

	// quaternion normalization
	inline quat_f normalize(const quat_f q) noexcept {
		float norm = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);

		// fallback
		if (norm == 0.0f) return identity_quat;

		float inv_norm = 1.0f / std::sqrt(norm);

		return quat_f{
			q.x * inv_norm,
			q.y * inv_norm,
			q.z * inv_norm,
			q.w * inv_norm
		};
	}

	// quaternion conjugation
	constexpr inline quat_f conjugate(const quat_f q) noexcept {
		return quat_f{
			-q.x,
			-q.y,
			-q.z,
			q.w
		};
	}

	// quaternion inverse
	constexpr inline quat_f inverse(const quat_f q) noexcept {
		float norm = (q.x * q.x) + (q.y * q.y) + (q.z * q.z) + (q.w * q.w);

		if (norm == 0.0f) return identity_quat;

		float inv_norm = 1.0f / norm;
		quat_f cq = conjugate(q);

		return quat_f{
			cq.x * inv_norm,
			cq.y * inv_norm,
			cq.z * inv_norm,
			cq.w * inv_norm
		};
	}

	// quaternion spherical interpolation
	inline quat_f slerp(const quat_f a, const quat_f b, float t) noexcept {
		float cos_theta = dot(a, b);
		quat_f dest = b;

		if (cos_theta < 0.0f) {
			cos_theta = -cos_theta;
			dest = quat_f{-b.x, -b.y, -b.z, -b.w};
		}

		if (cos_theta > 1.0f - epsilon<float>()) {
			return normalize(quat_f{
				a.x + t * (dest.x - a.x),
				a.y + t * (dest.y - a.y),
				a.z + t * (dest.z - a.z),
				a.w + t * (dest.w - a.w),
			});
		}

		float theta = std::acos(cos_theta);
		float sin_theta = std::sin(theta);

		float inv_sin = 1.0f / sin_theta;

		float w1 = std::sin((1.0f - t) * theta) * inv_sin;
		float w2 = std::sin(t * theta) * inv_sin;

		return quat_f{
			(w1 * a.x) + (w2 * dest.x),
			(w1 * a.y) + (w2 * dest.y),
			(w1 * a.z) + (w2 * dest.z),
			(w1 * a.w) + (w2 * dest.w)
		};
	}
}
